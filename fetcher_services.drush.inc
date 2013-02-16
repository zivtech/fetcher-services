<?php

// If you have this installed as a drush extension and have the module on the
// same site, be sure not to redeclare this funciton.
if (!function_exists('fetcher_services_fetcher_search_paths')) {
  /**
   * Implements hook_fetcher_search_paths().
   */
  function fetcher_services_fetcher_search_paths() {
    // TODO: use a proper method for discovering the base path to the cmd file
    $path = explode('/', __FILE__);
    array_pop($path);
    $path = implode('/', $path) . '/lib/';
    return array(
      // Classes in base Fetcher install.
      $path,
    );
  }
}

/**
 * Implements hook_drush_command().
 */
function fetcher_services_drush_command() {
  $items = array();
  $items['fetcher-services-cron'] = array(
    'description' => 'Run cron on all sites listed on this host in the fetcher services database.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  return $items;
}

/**
 * Print out information about a single site.
 */
function drush_fetcher_services_cron($site_name = NULL) {
  $site = drush_fetcher_get_site();
  $options = array(
    'server-hostname' => $site['system']->getHostname(),
  );
  $sites = drush_fetcher_get_info_fetcher('', 0, $options)
    ->listSites();
  drush_print_r($sites);
}

