<?php
/**
 * @file
 * ignition_sites.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function ignition_sites_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass;
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'ignition';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'ignition/api';
  $endpoint->authentication = array(
    'ignition_sites' => 'ignition_sites',
    'services' => 'services',
  );
  $endpoint->server_settings = array();
  $endpoint->resources = array(
    'ignition-site' => array(
      'alias' => 'site',
      'operations' => array(
        'index' => array(
          'enabled' => 1,
        ),
      ),
    ),
  );
  $endpoint->debug = 0;
  $export['ignition'] = $endpoint;

  return $export;
}
