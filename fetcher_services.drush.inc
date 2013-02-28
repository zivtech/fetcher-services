<?php

// If you have this installed as a drush extension and have the module on the
// same site, be sure not to redeclare any of these functions.
if (!function_exists('fetcher_services_fetcher_search_paths')) {

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

}
