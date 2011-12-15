<?php

/**
 * Callback for listing sites.
 *
 * @param int $page
 * @param array $parameters
 * @return array
 */
function _ignition_sites_index($page, $parameters) {
  $sites = array();
  $query = new EntityFieldQuery('node');
  $query->entityCondition('bundle', 'ignition_site');
  $sites[] = 'foo';
  return $sites;
}
