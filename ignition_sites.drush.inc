<?php

/**
 * Implements hook_ignition_search_paths().
 */
function ignition_sites_ignition_search_paths() {
  // TODO: use a proper method for discovering the base path to the cmd file
  $path = explode('/', __FILE__);
  array_pop($path);
  $path = implode('/', $path) . '/lib/';
  return array(
    // Classes in base Ignition install.
    $path,
  );
}
