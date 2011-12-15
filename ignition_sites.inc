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
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ignition_site');
  $results = $query->execute();
  foreach ($results[node] as $nid => $node_data) {
    $sites[] = $node_data;
  }
  return $sites;
}
