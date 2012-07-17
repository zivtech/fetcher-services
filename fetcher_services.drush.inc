<?php

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
