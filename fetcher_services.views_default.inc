<?php
/**
 * @file
 * fetcher_services.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function fetcher_services_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'fetcher_servers';
  $view->description = 'Servers available to Fetcher';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Fetcher Servers';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Fetcher Servers';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create fetcher_server content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_ftchr_remote_host' => 'field_ftchr_remote_host',
    'field_ftchr_server_ip' => 'field_ftchr_server_ip',
    'field_ftchr_server_machine_name' => 'field_ftchr_server_machine_name',
    'field_ftchr_remote_user' => 'field_ftchr_remote_user',
    'field_ftchr_server_os' => 'field_ftchr_server_os',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ftchr_remote_host' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ftchr_server_ip' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ftchr_server_machine_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ftchr_remote_user' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ftchr_server_os' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = 'A quick glance of important information about Fetcher Servers. Click through to view notes. 

*Listed alphabetically

<a href="/node/add/fetcher-site">+ Add a site</a>  <a href="/node/add/fetcher-server">+ Add a server</a>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Host Name */
  $handler->display->display_options['fields']['field_ftchr_remote_host']['id'] = 'field_ftchr_remote_host';
  $handler->display->display_options['fields']['field_ftchr_remote_host']['table'] = 'field_data_field_ftchr_remote_host';
  $handler->display->display_options['fields']['field_ftchr_remote_host']['field'] = 'field_ftchr_remote_host';
  /* Field: Content: IP Address */
  $handler->display->display_options['fields']['field_ftchr_server_ip']['id'] = 'field_ftchr_server_ip';
  $handler->display->display_options['fields']['field_ftchr_server_ip']['table'] = 'field_data_field_ftchr_server_ip';
  $handler->display->display_options['fields']['field_ftchr_server_ip']['field'] = 'field_ftchr_server_ip';
  /* Field: Content: Machine Name */
  $handler->display->display_options['fields']['field_ftchr_server_machine_name']['id'] = 'field_ftchr_server_machine_name';
  $handler->display->display_options['fields']['field_ftchr_server_machine_name']['table'] = 'field_data_field_ftchr_server_machine_name';
  $handler->display->display_options['fields']['field_ftchr_server_machine_name']['field'] = 'field_ftchr_server_machine_name';
  /* Field: Content: Remote User */
  $handler->display->display_options['fields']['field_ftchr_remote_user']['id'] = 'field_ftchr_remote_user';
  $handler->display->display_options['fields']['field_ftchr_remote_user']['table'] = 'field_data_field_ftchr_remote_user';
  $handler->display->display_options['fields']['field_ftchr_remote_user']['field'] = 'field_ftchr_remote_user';
  /* Field: Content: Server Version */
  $handler->display->display_options['fields']['field_ftchr_server_os']['id'] = 'field_ftchr_server_os';
  $handler->display->display_options['fields']['field_ftchr_server_os']['table'] = 'field_data_field_ftchr_server_os';
  $handler->display->display_options['fields']['field_ftchr_server_os']['field'] = 'field_ftchr_server_os';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'fetcher_server' => 'fetcher_server',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/reports/fetcher-servers';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Fetcher Servers';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Sites on This Server */
  $handler = $view->new_display('block', 'Sites on This Server', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Sites on This Server';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Environment (field_ftchr_environment) */
  $handler->display->display_options['relationships']['field_ftchr_environment_value']['id'] = 'field_ftchr_environment_value';
  $handler->display->display_options['relationships']['field_ftchr_environment_value']['table'] = 'field_data_field_ftchr_environment';
  $handler->display->display_options['relationships']['field_ftchr_environment_value']['field'] = 'field_ftchr_environment_value';
  $handler->display->display_options['relationships']['field_ftchr_environment_value']['delta'] = '-1';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_ftchr_server_target_id']['id'] = 'field_ftchr_server_target_id';
  $handler->display->display_options['relationships']['field_ftchr_server_target_id']['table'] = 'field_data_field_ftchr_server';
  $handler->display->display_options['relationships']['field_ftchr_server_target_id']['field'] = 'field_ftchr_server_target_id';
  $handler->display->display_options['relationships']['field_ftchr_server_target_id']['relationship'] = 'field_ftchr_environment_value';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_ftchr_server_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'fetcher_site' => 'fetcher_site',
  );
  $export['fetcher_servers'] = $view;

  $view = new view();
  $view->name = 'fetcher_sites';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Fetcher sites';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Fetcher Sites';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create fetcher_site content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '125';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_ftchr_machine_name' => 'field_ftchr_machine_name',
    'field_ftchr_server' => 'field_ftchr_server',
    'field_ftchr_site_vcs_url' => 'field_ftchr_site_vcs_url',
    'field_ftchr_site_support' => 'field_ftchr_site_support',
  );
  $handler->display->display_options['style_options']['default'] = 'title';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ftchr_machine_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ftchr_server' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ftchr_site_vcs_url' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ftchr_site_support' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a href="/node/add/fetcher-site">+ Add a site</a>  <a href="/node/add/fetcher-server">+ Add a server</a>';
  $handler->display->display_options['header']['area']['format'] = '1';
  /* Relationship: Content: Environment (field_ftchr_environment) */
  $handler->display->display_options['relationships']['field_ftchr_environment_value']['id'] = 'field_ftchr_environment_value';
  $handler->display->display_options['relationships']['field_ftchr_environment_value']['table'] = 'field_data_field_ftchr_environment';
  $handler->display->display_options['relationships']['field_ftchr_environment_value']['field'] = 'field_ftchr_environment_value';
  $handler->display->display_options['relationships']['field_ftchr_environment_value']['label'] = 'Environment';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Machine Name */
  $handler->display->display_options['fields']['field_ftchr_machine_name']['id'] = 'field_ftchr_machine_name';
  $handler->display->display_options['fields']['field_ftchr_machine_name']['table'] = 'field_data_field_ftchr_machine_name';
  $handler->display->display_options['fields']['field_ftchr_machine_name']['field'] = 'field_ftchr_machine_name';
  /* Field: Field collection item: Server */
  $handler->display->display_options['fields']['field_ftchr_server']['id'] = 'field_ftchr_server';
  $handler->display->display_options['fields']['field_ftchr_server']['table'] = 'field_data_field_ftchr_server';
  $handler->display->display_options['fields']['field_ftchr_server']['field'] = 'field_ftchr_server';
  $handler->display->display_options['fields']['field_ftchr_server']['relationship'] = 'field_ftchr_environment_value';
  $handler->display->display_options['fields']['field_ftchr_server']['settings'] = array(
    'link' => 1,
  );
  /* Field: Content: VCS URL */
  $handler->display->display_options['fields']['field_ftchr_site_vcs_url']['id'] = 'field_ftchr_site_vcs_url';
  $handler->display->display_options['fields']['field_ftchr_site_vcs_url']['table'] = 'field_data_field_ftchr_site_vcs_url';
  $handler->display->display_options['fields']['field_ftchr_site_vcs_url']['field'] = 'field_ftchr_site_vcs_url';
  /* Field: Content: Drupal Support */
  $handler->display->display_options['fields']['field_ftchr_site_support']['id'] = 'field_ftchr_site_support';
  $handler->display->display_options['fields']['field_ftchr_site_support']['table'] = 'field_data_field_ftchr_site_support';
  $handler->display->display_options['fields']['field_ftchr_site_support']['field'] = 'field_ftchr_site_support';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'fetcher_site' => 'fetcher_site',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Drupal Support (field_ftchr_site_support) */
  $handler->display->display_options['filters']['field_ftchr_site_support_value']['id'] = 'field_ftchr_site_support_value';
  $handler->display->display_options['filters']['field_ftchr_site_support_value']['table'] = 'field_data_field_ftchr_site_support';
  $handler->display->display_options['filters']['field_ftchr_site_support_value']['field'] = 'field_ftchr_site_support_value';
  $handler->display->display_options['filters']['field_ftchr_site_support_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ftchr_site_support_value']['expose']['operator_id'] = 'field_ftchr_site_support_value_op';
  $handler->display->display_options['filters']['field_ftchr_site_support_value']['expose']['label'] = 'Drupal Support?';
  $handler->display->display_options['filters']['field_ftchr_site_support_value']['expose']['operator'] = 'field_ftchr_site_support_value_op';
  $handler->display->display_options['filters']['field_ftchr_site_support_value']['expose']['identifier'] = 'field_ftchr_site_support_value';
  $handler->display->display_options['filters']['field_ftchr_site_support_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/reports/fetcher-sites';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Fetcher Sites';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['fetcher_sites'] = $view;

  return $export;
}
