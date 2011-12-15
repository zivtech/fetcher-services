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
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $query->entityCondition('bundle', 'ignition_site');
  die(print_r($query->execute()));
  /*
  */
//  print_r($result);
  $sites[] = 'foo';
  return $sites;
}
