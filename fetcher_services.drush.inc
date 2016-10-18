<?php

// If you have this installed as a drush extension and have the module on the
// same site, be sure not to redeclare any of these functions.
if (!function_exists('fetcher_services_fetcher_search_paths')) {

// Here we match the nagios/sensu check pattern.
define('FETCHER_SERVICES_CHECK_OK', 0);
define('FETCHER_SERVICES_CHECK_WARNING', 1);
define('FETCHER_SERVICES_CHECK_CRITICAL', 2);
define('FETCHER_SERVICES_CHECK_UNKNOWN', 3);


/**
 * Implements hook_fetcher_search_paths().
 */
function fetcher_services_fetcher_search_paths() {
  return array(
    // Classes in base Fetcher Services.
    __DIR__ . '/lib/',
  );
}

/**
 * Implements hook_drush_command().
 */
function fetcher_services_drush_command() {
  $items = array();
  $items['fetcher-services-cron'] = array(
    'description' => 'Run cron on all sites listed on this host in the fetcher services database. This should normally be left blank.',
    'options' => array(
      'server-hostname' => 'If set explicity, used as the hostname to find the list of site environments on this server.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['fetcher-services-check-url'] = array(
    'description' => 'Check the http status of a url.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'url' => 'Check the http status code for this url.',
    ),
    'options' => array(
      'cached-url' => 'Allow checking of the cached version of the url. The default is NOT to use the cached version.',
    ),
  );
  $items['fetcher-services-check-all-urls'] = array(
    'description' => 'Check the http status of all fetcher urls.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'environment' => 'Check all sites of the given environment.',
    ),
    'options' => array(
      'support' => 'Check only the sites with or without support. This value must be either "true" or "false".',
    ),
  );

  return $items;
}

/**
 * Run cron on all sites on a given hostname.
 */
function drush_fetcher_services_cron($hostname = NULL) {
  $hostname = drush_get_option('server-hostname');
  $sites = drush_fetcher_get_sites_for_host($hostname);
  $failures = array();
  foreach ($sites as $site) {
    drush_log("Now executing: `drush cron --root={$site['site.webroot']} --uri={$site['hostname']}`", 'info');
    $command_options = array(
      "--root={$site['site.webroot']}",
      "--uri={$site['hostname']}",
    );
    $keys = array(
      '@name' => $site['name'],
      '@environment' => $site['environment.local'],
      '@webroot' => $site['site.webroot'],
      '@uri' => $site['hostname'],
    );
    drush_log(dt('Processing cron on @name in environment @environment at path `@webroot` with uri `@uri`.', $keys), 'ok');
    $output = drush_invoke_process($site['site.webroot'] . '#' . $site['hostname'], 'cron', array(), $command_options);
    if ($output['error_status']) {
      $failures[] = $site['name'] . '.' . $site['environment.local'];
      drush_log(dt('Failure processing cron on @name.@environment at @webroot#@uri.', $keys), 'error');
    }
  }
  if (!empty($failures)) {
    $message = dt('Error running cron for sites: @sites', array('@sites' => implode($failures, ', ')));
    drush_log('error', $message);
    drush_set_error('CRON_FAILURE', $message);
  }
}

/**
 * Drush command callback for verifying a url is up.
 */
function drush_fetcher_services_check_url($url) {
  if (filter_var($url, FILTER_VALIDATE_URL) === FALSE) {
    $exit_code = FETCHER_SERVICES_CHECK_WARNING;
    $error_message = dt('@url is not a valid url.', array('@url' => $url));
  }
  else {
    $curl_url = drush_get_option('cached-url') ? $url : $url . '?fetcher-check=' . time();
    $ch = curl_init($curl_url);
    curl_setopt($ch, CURLOPT_HEADER, TRUE);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);
    $data = curl_exec($ch);
    $status_code = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    curl_close($ch);
    $exit_code = $status_code != 200 ? FETCHER_SERVICES_CHECK_CRITICAL : FETCHER_SERVICES_CHECK_OK;

    if ($exit_code != CHECK_OK) {
      $error_message = dt('Received a @status_code on @url', array('@status_code' => $status_code, '@url' => $curl_url));
    }
  }

  if (!empty($error_message)) {
    $level = $exit_code == FETCHER_SERVICES_CHECK_CRITICAL ? 'critical' : 'error';
    drush_log($error_message, $error);
    drush_set_error($error_message);
  }
  drush_set_context('DRUSH_EXIT_CODE', $exit_code);
}

/**
 * Check the status of all of the urls of a given environment.
 */
function drush_fetcher_services_check_all_urls($environment) {
  $support = drush_get_option('support');
  $info = drush_fetcher_get_info_fetcher();
  $sites = $info->getSitesByEnvironment($environment, $support);

  $error_status = FETCHER_SERVICES_CHECK_OK;
  drush_set_context('DRUSH_EXIT_CODE', $error_status);
  if (empty($sites)) {
    drush_log(dt('No sites were checked.'), 'ok');
    return;
  }

  foreach ($sites as $site) {
    if (!empty($site['environments'][$environment]['uri'])) {
      $url = $site['environments'][$environment]['uri'];
      $parsed_url = parse_url($url);
      if (empty($parsed_url['scheme'])) {
        $url = 'http://' . $url;
      }
      $output = drush_invoke_process(NULL, 'fetcher-services-check-url', array($url));
      if ($output['error_status']) {
        $current_status = drush_get_context('DRUSH_EXIT_CODE');
        $error_status = $output['error_status'] > $current_status ? $output['error_status'] : $current_status;
        drush_set_context('DRUSH_EXIT_CODE', $error_status);
      }
    }
  }

  // Add a message if all sites are up and running.
  if (drush_get_context('DRUSH_EXIT_CODE') === FETCHER_SERVICES_CHECK_OK) {
    drush_log(dt('All sites are up and running.'), 'ok');
  }
}

}
