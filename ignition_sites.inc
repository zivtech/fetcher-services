<?php

/**
 * Callback for listing sites.
 *
 * @param int $page
 *   The page number to start with, defaults to 0.
 * @param string $parameters
 *   A string to search the sites with.
 * @return array
 *   A multidimensional array containing site name and client.
 */
function _ignition_sites_services_index_sites($page, $name, $name) {
  $sites = array();
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ignition_site')
    ->range($page, 100);
  if ($name != '') {
    $query = $query->fieldCondition('field_machine_name', 'value', $name, 'CONTAINS');
  }
  // TODO: Add optional $server param.
  $results = $query->execute();
  $nodes = node_load_multiple(array_keys($results[node]));
  $sites = array();
  foreach ($nodes as $nid => $node) {
    $site = entity_metadata_wrapper('node', $node);
    $sites[$site->field_machine_name->value()] = array(
      'name' => $site->title->value(),
      // TODO: add client reference.
      //'client' => $site->
    );
  }
  return $sites;
}

/**
 * Callback for listing info about a single site.
 *
 * @param $name
 *   The name of the site to list.
 * @param $parameters
 *   An array of parameters from the services request.
 */
function _ignition_sites_services_retrieve_site($name, $parameters) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ignition_site')
    // TODO: rename this site machine name since it has to be unique
    ->fieldCondition('field_machine_name', 'value', $name, '=')
    ->range($page, 50);
  $results = $query->execute();
  $site = entity_metadata_wrapper('node', node_load(reset(array_keys($results['node']))));
  $site_info = array();
  $site_info['name'] = $site->field_machine_name->value();
  $site_info['title'] = $site->title->value();
  $site_info['nid'] = $site->nid->value();
  $site_info['vcs'] = drupal_strtolower(_ignition_sites_get_list_display_value('field_site_vcs', $site->field_site_vcs->value()));
  $site_info['vcs_url'] = $site->field_site_vcs_url->value();
  // TODO: look up real values.
  $site_info['version'] = drupal_strtolower(_ignition_sites_get_list_display_value('field_site_drupal_version', $site->field_site_drupal_version->value()));
  $site_info['support'] = (boolean) $site->field_support->value();
  $site_info['private files'] = (boolean) $site->field_private_files->value();
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

/**
 * Returns the display value for a list field.
 *
 * @param $field
 *  The name of the field (e.g. `field_foo`).
 * @param $value
 *  The actual value of the field.
 */
function _ignition_sites_get_list_display_value($field, $value) {
  $field_info = field_info_field($field);
  if (isset($field_info['settings']['allowed_values'][$value])) {
    return $field_info['settings']['allowed_values'][$value];
  }
  else {
    return FALSE;
  }
}
