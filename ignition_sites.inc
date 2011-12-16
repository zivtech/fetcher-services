<?php

/**
 * Callback for listing sites.
 *
 * @param int $page
 *   
 * @param string $parameters
 *   
 * @return array
 */
function _ignition_sites_index($page, $name, $name) {
  $sites = array();
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ignition_site')
    ->range($page, 50);
  if ($name != '') {
    $query = $query->fieldCondition('field_machine_name', 'value', $name, 'CONTAINS');
  }
  $results = $query->execute();
  $nodes = node_load_multiple(array_keys($results[node]));
  foreach ($nodes as $nid => $node) {
    $site_info = array();
    $site = entity_metadata_wrapper('node', $node);
    $site_info['name'] = $site->title->value();
    $site_info['nid'] = $nid;
    $site_info['vcs'] = $site->field_site_vcs->value();
    // TODO: look up real values.
    $site_info['version'] = $site->field_site_drupal_version->value();
    $site_info['support'] = $site->field_support->value();
    $site_info['private files'] = $site->field_private_files->value();
    foreach ($site->field_environment->value() as $environment) {
      $environment = entity_metadata_wrapper('field_collection_item', $environment);
      $data = array();
      $server = entity_metadata_wrapper('node', $environment->field_server->value());
      $name = $server->field_server_machine_name->value();
      $data['server']['name'] = $name;
      $data['server']['hostname'] = $server->field_server_hostname->value();
      // TODO: make this smart.
      $data['code hosts'][] = $name;
      $data['files host'] = $name;
      $data['mysql host'] = $name;
      $data['server']['hostname'] = $server->field_server_hostname->value();
      $site_info['environments'][$environment->field_environment_name->value()] = $data;
    }
    $sites[$site->field_machine_name->value()] = $site_info;
  }
  return $sites;
}

function _ignition_sites_retrieve($name, $parameters) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ignition_site')
    // TODO: rename this site machine name since it has to be unique
    ->fieldCondition('field_machine_name', 'value', $name, '=')
    ->range($page, 50);
  $results = $query->execute();
  $site = entity_metadata_wrapper('node', node_load(reset(array_keys($results['node']))));
  $site_info = array();
  $site_info['name'] = $site->title->value();
  $site_info['nid'] = $site->nid->value();
  $site_info['vcs'] = $site->field_site_vcs->value();
  // TODO: look up real values.
  $site_info['version'] = $site->field_site_drupal_version->value();
  $site_info['support'] = $site->field_support->value();
  $site_info['private files'] = $site->field_private_files->value();
  foreach ($site->field_environment->value() as $environment) {
    $environment = entity_metadata_wrapper('field_collection_item', $environment);
    $data = array();
    $server = entity_metadata_wrapper('node', $environment->field_server->value());
    $name = $server->field_server_machine_name->value();
    $data['server']['name'] = $name;
    $data['server']['hostname'] = $server->field_server_hostname->value();
    // TODO: make this smart.
    $data['code hosts'][] = $name;
    $data['files host'] = $name;
    $data['mysql host'] = $name;
    $data['server']['hostname'] = $server->field_server_hostname->value();
    $site_info['environments'][$environment->field_environment_name->value()] = $data;
  }
  return $site_info;
}
