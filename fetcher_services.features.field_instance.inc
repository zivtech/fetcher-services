<?php
/**
 * @file
 * fetcher_services.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function fetcher_services_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'field_collection_item-field_ftchr_environment-field_field_ftchr_vcs_rootsubdir'
  $field_instances['field_collection_item-field_ftchr_environment-field_field_ftchr_vcs_rootsubdir'] = array(
    'bundle' => 'field_ftchr_environment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If the root of this VCS repository is not the root of the Drupal htdocs (the folder containing `index.php`, specify the subdirectory containing it.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 13,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_field_ftchr_vcs_rootsubdir',
    'label' => 'Version Control Doc Root Subdirectory',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_ftchr_environment-field_ftchr_branch'
  $field_instances['field_collection_item-field_ftchr_environment-field_ftchr_branch'] = array(
    'bundle' => 'field_ftchr_environment',
    'default_value' => array(
      0 => array(
        'value' => 'master',
      ),
    ),
    'deleted' => 0,
    'description' => 'With git this defaults to `master`, on svn it defaults to `trunk`.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 10,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_ftchr_branch',
    'label' => 'Version Control Branch',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_ftchr_environment-field_ftchr_db'
  $field_instances['field_collection_item-field_ftchr_environment-field_ftchr_db'] = array(
    'bundle' => 'field_ftchr_environment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The name of the remote database for this site. If left blank, the site\'s machine name will be used.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 14,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_ftchr_db',
    'label' => 'Database',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_ftchr_environment-field_ftchr_drupal_version'
  $field_instances['field_collection_item-field_ftchr_environment-field_ftchr_drupal_version'] = array(
    'bundle' => 'field_ftchr_environment',
    'default_value' => NULL,
    'default_value_function' => '',
    'default_value_php' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 9,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_ftchr_drupal_version',
    'label' => 'Drupal version',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 0,
      ),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_ftchr_environment-field_ftchr_environment_name'
  $field_instances['field_collection_item-field_ftchr_environment-field_ftchr_environment_name'] = array(
    'bundle' => 'field_ftchr_environment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_ftchr_environment_name',
    'label' => 'Environment',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'select_or_other',
      'settings' => array(
        'available_options' => 'dev|Dev
staging|Staging
prod|Production',
        'available_options_php' => '',
        'markup_available_options_php' => '&lt;none&gt;',
        'other' => 'Other',
        'other_title' => '',
        'other_unknown_defaults' => 'ignore',
        'sort_options' => 0,
      ),
      'type' => 'select_or_other',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_ftchr_environment-field_ftchr_root'
  $field_instances['field_collection_item-field_ftchr_environment-field_ftchr_root'] = array(
    'bundle' => 'field_ftchr_environment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'This is optional and will default to `/var/www/[site name]/webroot`.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_ftchr_root',
    'label' => 'Remote Server Site Root',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_ftchr_environment-field_ftchr_server'
  $field_instances['field_collection_item-field_ftchr_environment-field_ftchr_server'] = array(
    'bundle' => 'field_ftchr_environment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 11,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_ftchr_server',
    'label' => 'Server',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 0,
      ),
      'type' => 'options_select',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'field_collection_item-field_ftchr_environment-field_ftchr_uri'
  $field_instances['field_collection_item-field_ftchr_environment-field_ftchr_uri'] = array(
    'bundle' => 'field_ftchr_environment',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'field_collection_item',
    'field_name' => 'field_ftchr_uri',
    'label' => 'URI',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'node-fetcher_server-body'
  $field_instances['node-fetcher_server-body'] = array(
    'bundle' => 'fetcher_server',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 9,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'trim_length' => 600,
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Notes',
    'required' => 0,
    'settings' => array(
      'display_summary' => 1,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-fetcher_server-field_ftchr_remote_host'
  $field_instances['node-fetcher_server-field_ftchr_remote_host'] = array(
    'bundle' => 'fetcher_server',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The host name of this server.  This should be a proper fully qualified domain name (FQDN) that can be used to publicly address this server.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 15,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ftchr_remote_host',
    'label' => 'Host Name',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-fetcher_server-field_ftchr_remote_user'
  $field_instances['node-fetcher_server-field_ftchr_remote_user'] = array(
    'bundle' => 'fetcher_server',
    'default_value' => array(
      0 => array(
        'value' => 'webadmin',
      ),
    ),
    'deleted' => 0,
    'description' => 'The user name of the user to log in to this server.  If you have a shared sign on system (LDAP or similar) this may be ignored.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 16,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ftchr_remote_user',
    'label' => 'Remote User',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 31,
    ),
  );

  // Exported field_instance: 'node-fetcher_server-field_ftchr_server_ip'
  $field_instances['node-fetcher_server-field_ftchr_server_ip'] = array(
    'bundle' => 'fetcher_server',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ftchr_server_ip',
    'label' => 'IP Address',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-fetcher_server-field_ftchr_server_machine_name'
  $field_instances['node-fetcher_server-field_ftchr_server_machine_name'] = array(
    'bundle' => 'fetcher_server',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'editablefields',
        'settings' => array(
          'click_to_edit' => 0,
          'empty_text' => '',
          'fallback_format' => 'machine_name_default',
          'fallback_settings' => array(),
        ),
        'type' => 'editable',
        'weight' => 13,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ftchr_server_machine_name',
    'label' => 'Machine Name',
    'required' => 0,
    'settings' => array(
      'source' => 'title',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'machine_name',
      'settings' => array(
        'size' => 128,
      ),
      'type' => 'machine_name_default',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-fetcher_server-field_ftchr_server_managed'
  $field_instances['node-fetcher_server-field_ftchr_server_managed'] = array(
    'bundle' => 'fetcher_server',
    'default_value' => NULL,
    'default_value_function' => '',
    'default_value_php' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 7,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ftchr_server_managed',
    'label' => 'Managed By',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 0,
      ),
      'type' => 'options_select',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'node-fetcher_server-field_ftchr_server_os'
  $field_instances['node-fetcher_server-field_ftchr_server_os'] = array(
    'bundle' => 'fetcher_server',
    'default_value' => NULL,
    'default_value_function' => '',
    'default_value_php' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 8,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ftchr_server_os',
    'label' => 'Server Version',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 0,
      ),
      'type' => 'options_select',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-fetcher_site-body'
  $field_instances['node-fetcher_site-body'] = array(
    'bundle' => 'fetcher_site',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 6,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 17,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'trim_length' => 600,
        'type' => 'text_summary_or_trimmed',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Additional Notes',
    'required' => FALSE,
    'settings' => array(
      'display_summary' => TRUE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-fetcher_site-field_ftchr_environment'
  $field_instances['node-fetcher_site-field_ftchr_environment'] = array(
    'bundle' => 'fetcher_site',
    'default_value' => array(
      0 => array(
        '_weight' => NULL,
        'entity' => entity_import('field_collection_item', '{
          "item_id" : null,
          "revision_id" : null,
          "field_name" : "field_ftchr_environment",
          "default_revision" : true,
          "archived" : false,
          "field_field_ftchr_vcs_rootsubdir" : { "und" : [] },
          "field_ftchr_branch" : { "und" : [ { "value" : "master" } ] },
          "field_ftchr_drupal_version" : { "und" : [] },
          "field_ftchr_environment_name" : { "und" : [] },
          "field_ftchr_root" : { "und" : [] },
          "field_ftchr_server" : { "und" : [] },
          "field_ftchr_uri" : { "und" : [] },
          "field_ftchr_db" : { "und" : [] }
        }'),
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'field_collection',
        'settings' => array(
          'add' => 'Add',
          'delete' => 'Delete',
          'description' => TRUE,
          'edit' => 'Edit',
          'view_mode' => 'full',
        ),
        'type' => 'field_collection_view',
        'weight' => 9,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ftchr_environment',
    'label' => 'Environment',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'field_collection',
      'settings' => array(),
      'type' => 'field_collection_embed',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-fetcher_site-field_ftchr_machine_name'
  $field_instances['node-fetcher_site-field_ftchr_machine_name'] = array(
    'bundle' => 'fetcher_site',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'editablefields',
        'settings' => array(
          'click_to_edit' => FALSE,
          'empty_text' => '',
          'fallback_format' => NULL,
          'fallback_settings' => array(),
        ),
        'type' => 'editable',
        'weight' => 0,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ftchr_machine_name',
    'label' => 'Machine Name',
    'required' => 0,
    'settings' => array(
      'source' => 'title',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'machine_name',
      'settings' => array(
        'size' => 128,
      ),
      'type' => 'machine_name_default',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-fetcher_site-field_ftchr_site_support'
  $field_instances['node-fetcher_site-field_ftchr_site_support'] = array(
    'bundle' => 'fetcher_site',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      2 => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
      3 => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
      4 => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 3,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'full' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'label' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 15,
      ),
      'token' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ftchr_site_support',
    'label' => 'Drupal Support',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'weight' => 2,
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
      ),
      'type' => 'options_onoff',
      'weight' => 5,
    ),
    'widget_type' => 'optionwidgets_onoff',
  );

  // Exported field_instance: 'node-fetcher_site-field_ftchr_site_vcs'
  $field_instances['node-fetcher_site-field_ftchr_site_vcs'] = array(
    'bundle' => 'fetcher_site',
    'default_value' => array(
      0 => array(
        'value' => 1,
      ),
    ),
    'default_value_function' => '',
    'default_value_php' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 2,
      ),
      'extranet_lead_display' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ftchr_site_vcs',
    'label' => 'Version Control System',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 0,
      ),
      'type' => 'options_select',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-fetcher_site-field_ftchr_site_vcs_url'
  $field_instances['node-fetcher_site-field_ftchr_site_vcs_url'] = array(
    'bundle' => 'fetcher_site',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 8,
      ),
      'extranet_lead_display' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'issuemetadata' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ftchr_site_vcs_url',
    'label' => 'VCS URL',
    'required' => FALSE,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional Notes');
  t('Database');
  t('Drupal Support');
  t('Drupal version');
  t('Environment');
  t('Host Name');
  t('IP Address');
  t('If the root of this VCS repository is not the root of the Drupal htdocs (the folder containing `index.php`, specify the subdirectory containing it.');
  t('Machine Name');
  t('Managed By');
  t('Notes');
  t('Remote Server Site Root');
  t('Remote User');
  t('Server');
  t('Server Version');
  t('The host name of this server.  This should be a proper fully qualified domain name (FQDN) that can be used to publicly address this server.');
  t('The name of the remote database for this site. If left blank, the site\'s machine name will be used.');
  t('The user name of the user to log in to this server.  If you have a shared sign on system (LDAP or similar) this may be ignored.');
  t('This is optional and will default to `/var/www/[site name]/webroot`.');
  t('URI');
  t('VCS URL');
  t('Version Control Branch');
  t('Version Control Doc Root Subdirectory');
  t('Version Control System');
  t('With git this defaults to `master`, on svn it defaults to `trunk`.');

  return $field_instances;
}
