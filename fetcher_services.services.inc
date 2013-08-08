<?php
/**
 * @file
 * fetcher_services.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function fetcher_services_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'fetcher';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'fetcher/api';
  $endpoint->authentication = array(
    'fetcher_services' => 'fetcher_services',
  );
  $endpoint->server_settings = array(
    'rest_server' => array(),
  );
  $endpoint->resources = array(
    'fetcher-site' => array(
      'alias' => 'site',
      'operations' => array(
        'index' => array(
          'enabled' => 1,
        ),
        'retrieve' => array(
          'enabled' => 1,
        ),
      ),
    ),
  );
  $endpoint->debug = 0;
  $export['fetcher'] = $endpoint;

  return $export;
}
