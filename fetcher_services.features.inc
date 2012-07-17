<?php
/**
 * @file
 * fetcher_services.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function fetcher_services_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function fetcher_services_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_node_info().
 */
function fetcher_services_node_info() {
  $items = array(
    'project_info' => array(
      'name' => t('Site'),
      'base' => 'node_content',
      'description' => t('A site that Zivtech created or maintains and the associated access information.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'server' => array(
      'name' => t('Server'),
      'base' => 'node_content',
      'description' => t('A server that zivtech runs or maintains.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
