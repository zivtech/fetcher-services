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
    'description' => 'Run cron on all sites listed on this host in the fetcher services database.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'options' => array(
      'server-hostname' => 'If set explicity, used as the hostname to find the list of site environments on this server.',
    ),
  );
  return $items;
}

/**
 * Print out information about a single site.
 */
function drush_fetcher_services_cron($site_name = NULL) {
  $hostname = drush_get_option('server-hostname');
  $sites = drush_fetcher_services_get_sites_for_host($hostname);
  foreach ($sites as $site) {
    drush_log("Now executing: `drush cron --root={$site['site.webroot']} --uri={$site['hostname']}`", 'info');
    $command_options = array(
      "--root={$site['site.webroot']}",
      "--uri={$site['hostname']}",
    );
    $failures = array();
    $keys = array(
      '@name' => $site['name'],
      '@path' => $site['environment.local'],
      '@webroot' => $site['site.webroot'],
      '@uri' => $site['hostname'],
    );
    drush_log(dt('Processing cron on @name in environment @path at path `@webroot` with uri `@uri`.', $keys), 'ok');
    if (!drush_invoke_process($site['site.webroot'] . '#' . $site['hostname'], 'cron', array(), $command_options)) {
      $failures[] = $site['name'] . ':' . $site['environment.local'];
      drush_log(dt('Failure processing cron on @name in environment @path.', $keys), 'error');
    }
    if (count($failures)) {
      drush_set_error('CRON_FAILURE', dt('Error running cron for sites: @sites', array('@sites' => implode($failures, ', '))));
    }
  }
}

/**
 * Get an array of fetcher sites for all environments on a host.
 */
function drush_fetcher_services_get_sites_for_host($hostname = NULL) {
  $site = drush_fetcher_get_site();
  if (is_null($hostname)) {
    $hostname = $site['system']->getHostname();
  }
  $options = array(
    'detail' => 'true',
    'server-hostname' => $hostname,
  );
  $site_info_list = drush_fetcher_get_info_fetcher()
    ->listSites('', 0, $options);
  $arrayify = function ($object) use (&$arrayify) {
    if (is_object($object)) {
      foreach ($object as &$item) {
        if (is_object($item)) {
          $item = $arrayify($item);
        }
      }
    }
    return (array) $object;
  };
  $sites = array();
  foreach ($site_info_list as $site_info) {
    $site_info = $arrayify($site_info);
    foreach ($site_info['environments'] as $name => $environment) {
      $local_site_info = array_merge($site_info, $environment);
      $site = drush_fetcher_get_site($local_site_info);
      $site['environment.local'] = $name;
      $sites[] = $site;
    }
  }
  return $sites;
}

}
