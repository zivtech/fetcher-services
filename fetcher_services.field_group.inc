<?php
/**
 * @file
 * fetcher_services.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function fetcher_services_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ftchr_advanced|field_collection_item|field_ftchr_environment|form';
  $field_group->group_name = 'group_ftchr_advanced';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_ftchr_environment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Advanced',
    'weight' => '5',
    'children' => array(
      0 => 'field_field_ftchr_vcs_rootsubdir',
      1 => 'field_ftchr_branch',
      2 => 'field_ftchr_root',
      3 => 'field_ftchr_working_dir',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-ftchr-advanced field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_ftchr_advanced|field_collection_item|field_ftchr_environment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_server_info|node|fetcher_server|form';
  $field_group->group_name = 'group_server_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fetcher_server';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Server Info',
    'weight' => '2',
    'children' => array(
      0 => 'field_ftchr_server_ip',
      1 => 'field_ftchr_server_managed',
      2 => 'field_ftchr_server_os',
      3 => 'field_ftchr_remote_host',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-server-info field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_server_info|node|fetcher_server|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Advanced');
  t('Server Info');

  return $field_groups;
}
