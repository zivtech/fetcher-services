<?php
/**
 * @file
 * fetcher_services.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function fetcher_services_taxonomy_default_vocabularies() {
  return array(
    'server_services' => array(
      'name' => 'Server Services',
      'machine_name' => 'server_services',
      'description' => 'The services that are running on this server.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'vocabulary_1' => array(
      'name' => 'Category',
      'machine_name' => 'vocabulary_1',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
