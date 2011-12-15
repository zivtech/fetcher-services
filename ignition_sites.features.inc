<?php
/**
 * @file
 * ignition_sites.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ignition_sites_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_views_api().
 */
function ignition_sites_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => 3.0);
  }
}

/**
 * Implementation of hook_node_info().
 */
function ignition_sites_node_info() {
  $items = array(
    'ignition_site' => array(
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
