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

  $view = new view;
  $view->name = 'projects';
  $view->description = '';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = 'Projects';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Projects';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer nodes';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_project_company' => 'field_project_company',
    'entity_id' => 'entity_id',
    'entity_id_3' => 'entity_id_3',
    'entity_id_1' => 'entity_id_1',
    'edit_node' => 'title',
    'entity_id_2' => 'entity_id_2',
    'entity_id_5' => 'entity_id_5',
    'entity_id_4' => 'entity_id_4',
    'field_project_notes' => 'field_project_notes',
    'field_project_amount_budgeted' => 'field_project_amount_budgeted',
    'field_amount_complete' => 'field_amount_complete',
    'changed' => 'changed',
  );
  $handler->display->display_options['style_options']['default'] = 'entity_id_2';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
    ),
    'field_project_company' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id' => array(
      'align' => '',
      'separator' => '',
    ),
    'entity_id_3' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_1' => array(
      'align' => '',
      'separator' => '',
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
    ),
    'entity_id_2' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_5' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'entity_id_4' => array(
      'align' => '',
      'separator' => '',
    ),
    'field_project_notes' => array(
      'align' => '',
      'separator' => '',
    ),
    'field_project_amount_budgeted' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_amount_complete' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'changed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 1;
  $handler->display->display_options['style_options']['order'] = 'desc';
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<a href="/node/add/project">+ Add new project</a>
<h3>Activity Level Scale</h3>
<b>0 = Inactive</b>, <b>1 = Barely active</b>, <b>2 = Some activity</b>, <b>3 = Normal activity</b>, <b>4 = Heavy activity</b>, <b>5 = Aggressive deadline, urgent</b>.';
  $handler->display->display_options['header']['area']['format'] = '2';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_project_company']['id'] = 'field_project_company';
  $handler->display->display_options['fields']['field_project_company']['table'] = 'field_data_field_project_company';
  $handler->display->display_options['fields']['field_project_company']['field'] = 'field_project_company';
  $handler->display->display_options['fields']['field_project_company']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_company']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_company']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_project_company']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_project_company']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_project_company']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_project_company']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_project_company']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_company']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_company']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_company']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_project_company']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_company']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_project_company']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_project_company']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_company']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_company']['hide_alter_empty'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'field_data_field_dev_lead';
  $handler->display->display_options['fields']['entity_id']['field'] = 'field_dev_lead';
  $handler->display->display_options['fields']['entity_id']['label'] = 'Dev Lead';
  $handler->display->display_options['fields']['entity_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['entity_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['entity_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['entity_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['entity_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['entity_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['entity_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['entity_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['entity_id']['hide_alter_empty'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['entity_id_3']['id'] = 'entity_id_3';
  $handler->display->display_options['fields']['entity_id_3']['table'] = 'field_data_field_main_contact';
  $handler->display->display_options['fields']['entity_id_3']['field'] = 'field_main_contact';
  $handler->display->display_options['fields']['entity_id_3']['label'] = 'PM';
  $handler->display->display_options['fields']['entity_id_3']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['alter']['external'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['entity_id_3']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['entity_id_3']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['alter']['html'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['entity_id_3']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['entity_id_3']['hide_empty'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['empty_zero'] = 0;
  $handler->display->display_options['fields']['entity_id_3']['hide_alter_empty'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['entity_id_1']['id'] = 'entity_id_1';
  $handler->display->display_options['fields']['entity_id_1']['table'] = 'field_data_field_internal_lead';
  $handler->display->display_options['fields']['entity_id_1']['field'] = 'field_internal_lead';
  $handler->display->display_options['fields']['entity_id_1']['label'] = 'Main Devs';
  $handler->display->display_options['fields']['entity_id_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['entity_id_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['entity_id_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['entity_id_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['entity_id_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['entity_id_1']['hide_alter_empty'] = 0;
  /* Field: Node: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_node']['element_type'] = 'em';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['edit_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_node']['empty_zero'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['entity_id_2']['id'] = 'entity_id_2';
  $handler->display->display_options['fields']['entity_id_2']['table'] = 'field_data_field_project_activity_level';
  $handler->display->display_options['fields']['entity_id_2']['field'] = 'field_project_activity_level';
  $handler->display->display_options['fields']['entity_id_2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['alter']['external'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['entity_id_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['entity_id_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['entity_id_2']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['entity_id_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['entity_id_2']['hide_alter_empty'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['entity_id_5']['id'] = 'entity_id_5';
  $handler->display->display_options['fields']['entity_id_5']['table'] = 'field_data_field_project_next_deadline';
  $handler->display->display_options['fields']['entity_id_5']['field'] = 'field_project_next_deadline';
  $handler->display->display_options['fields']['entity_id_5']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['alter']['external'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['entity_id_5']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['entity_id_5']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['alter']['html'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['entity_id_5']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['entity_id_5']['hide_empty'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['empty_zero'] = 0;
  $handler->display->display_options['fields']['entity_id_5']['hide_alter_empty'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['entity_id_4']['id'] = 'entity_id_4';
  $handler->display->display_options['fields']['entity_id_4']['table'] = 'field_data_field_sites';
  $handler->display->display_options['fields']['entity_id_4']['field'] = 'field_sites';
  $handler->display->display_options['fields']['entity_id_4']['label'] = 'Site';
  $handler->display->display_options['fields']['entity_id_4']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['alter']['external'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['entity_id_4']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['entity_id_4']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['alter']['html'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['entity_id_4']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['entity_id_4']['hide_empty'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['empty_zero'] = 0;
  $handler->display->display_options['fields']['entity_id_4']['hide_alter_empty'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_project_notes']['id'] = 'field_project_notes';
  $handler->display->display_options['fields']['field_project_notes']['table'] = 'field_data_field_project_notes';
  $handler->display->display_options['fields']['field_project_notes']['field'] = 'field_project_notes';
  $handler->display->display_options['fields']['field_project_notes']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_notes']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_notes']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_project_notes']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_project_notes']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_notes']['hide_alter_empty'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_project_amount_budgeted']['id'] = 'field_project_amount_budgeted';
  $handler->display->display_options['fields']['field_project_amount_budgeted']['table'] = 'field_data_field_project_amount_budgeted';
  $handler->display->display_options['fields']['field_project_amount_budgeted']['field'] = 'field_project_amount_budgeted';
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_amount_budgeted']['hide_alter_empty'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_amount_complete']['id'] = 'field_amount_complete';
  $handler->display->display_options['fields']['field_amount_complete']['table'] = 'field_data_field_amount_complete';
  $handler->display->display_options['fields']['field_amount_complete']['field'] = 'field_amount_complete';
  $handler->display->display_options['fields']['field_amount_complete']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_amount_complete']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_amount_complete']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_amount_complete']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_amount_complete']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_amount_complete']['hide_alter_empty'] = 0;
  /* Field: Last Updated */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['ui_name'] = 'Last Updated';
  $handler->display->display_options['fields']['changed']['label'] = 'Last Updated';
  $handler->display->display_options['fields']['changed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['changed']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['changed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['changed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['changed']['empty_zero'] = 0;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  /* Filter criterion: Broken/missing handler */
  $handler->display->display_options['filters']['field_project_activity_level_value']['id'] = 'field_project_activity_level_value';
  $handler->display->display_options['filters']['field_project_activity_level_value']['table'] = 'field_data_field_project_activity_level';
  $handler->display->display_options['filters']['field_project_activity_level_value']['field'] = 'field_project_activity_level_value';

  /* Display: Active Projects */
  $handler = $view->new_display('page', 'Active Projects', 'page_1');
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  /* Filter criterion: Broken/missing handler */
  $handler->display->display_options['filters']['field_project_activity_level_value']['id'] = 'field_project_activity_level_value';
  $handler->display->display_options['filters']['field_project_activity_level_value']['table'] = 'field_data_field_project_activity_level';
  $handler->display->display_options['filters']['field_project_activity_level_value']['field'] = 'field_project_activity_level_value';
  $handler->display->display_options['filters']['field_project_activity_level_value']['operator'] = '>';
  $handler->display->display_options['filters']['field_project_activity_level_value']['value'] = array(
    'value' => '0',
  );
  $handler->display->display_options['path'] = 'projects/active';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Active Projects';
  $handler->display->display_options['menu']['weight'] = '';
  $handler->display->display_options['menu']['name'] = 'primary-links';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Projects';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'primary-links';

  /* Display: All Projects */
  $handler = $view->new_display('page', 'All Projects', 'page_2');
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  $handler->display->display_options['path'] = 'projects/all';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'All Projects';
  $handler->display->display_options['menu']['weight'] = '1';
  $export['projects'] = $view;

  return $export;
}
