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
function _fetcher_services_services_index_sites($page, $name, $detail, $server_hostname) {
  $options = array(
    'name' => $name,
    'detail' => $detail,
    'server_hostname' => $server_hostname,
  );
  return _fetcher_service_get_list_of_sites($page, $options);
}

/**
 * Get a list of site data based on filter parameters.
 */
function _fetcher_service_get_list_of_sites($page, $options) {
  extract($options);
  $sites = array();
  $environment_filters = array();
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'fetcher_site')
    ->fieldOrderBy('field_ftchr_machine_name', 'value');
  $limit = isset($options['limit']) ? $options['limit'] : 1000;
  if ($limit) {
    $query->range($page, $limit);
  }
  if (!empty($options['name'])) {
    $query->fieldCondition('field_ftchr_machine_name', 'value', $name, 'CONTAINS');
  }
  if (!empty($options['server_hostname'])) {
    $environment_filters[] = array(
      'field' => 'field_ftchr_server',
      'column' => 'target_id',
      'value' => fetcher_services_lookup_server_nid_by_hostname($options['server_hostname']),
    );
  }
  if (!empty($options['ip_address'])) {
    $environment_filters[] = array(
      'field' => 'field_ftchr_server',
      'column' => 'target_id',
      'value' => fetcher_services_lookup_server_nid_by_ip_address($options['ip_address']),
    );
  }

  if (!empty($environment)) {
    $environment_filters[] = array(
      'field' => 'field_ftchr_environment_name',
      'column' => 'value',
      'value' => $environment,
    );
  }

  if (!empty($processes)) {
    $environment_filters[] = array(
      'field' => 'field_ftchr_site_processes',
      'column' => 'value',
      'value' => $processes,
    );
  }

  // IF we need to filter by values in the environments then do so here.
  if (!empty($environment_filters)) {
    $ids = fetcher_services_services_get_environment_ids($environment_filters);
    // Running this query with no ids will blow it up
    // so we end it here since there will be no results.
    if (empty($ids)) {
      return array();
    }
    $query->fieldCondition('field_ftchr_environment', 'value', $ids);
  }

  // Allow grabbing by published value.
  $published = isset($options['published']) ? $options['published'] : TRUE;
  if (!empty($published)) {
    $query->propertyCondition('status', 1);
  }
  else if ($published === FALSE) {
    $query->propertyCondition('status', 0);
  }

  if (isset($support)) {
    // Support must be either 0 or 1.
    $query->fieldCondition('field_ftchr_site_support', 'value', (int) $support);
  }

  $results = $query->execute();
  $nodes = node_load_multiple(array_keys($results['node']));
  $sites = array();
  foreach ($nodes as $nid => $node) {
    if ($detail) {
      $site_info_options = array();
      if (!empty($options['server_hostname'])) {
        $site_info_options['server_hostname'] = $server_hostname;
      }
      if (!empty($options['ip_address'])) {
        $site_info_options['server_ip_address'] = $ip_address;
      }
      $site = _fetcher_services_build_site_info($nid, $site_info_options);
      $sites[$site['name']] = $site;
    }
    else {
      $site = entity_metadata_wrapper('node', $node);
      $sites[$node->field_ftchr_machine_name[$node->language][0]['value']] = array(
        'title' => $site->title->value(),
      );
    }
  }
  if ($detail) {
    array_walk($sites, '_fetcher_services_services_trim');
  }
  return $sites;
}

/**
 * Utility function to trim a keya nd value for use with array_walk().
 */
function _fetcher_services_services_trim(&$name, &$value) {
  if (is_string($name)) {
    $name = trim($name);
  }
  if (is_string($value)) {
    $value = trim($value);
  }
};


/**
 * Callback for listing info about a single site.
 *
 * @param $name
 *   The name of the site to list.
 * @param $parameters
 *   An array of parameters from the services request.
 */
function _fetcher_services_services_retrieve_site($name, $parameters = NULL) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'fetcher_site')
    // TODO: rename this site machine name since it has to be unique
    ->fieldCondition('field_ftchr_machine_name', 'value', $name, '=');
  $results = $query->execute();
  if (!count($results)) {
    return FALSE;
  }
  $site_info = _fetcher_services_build_site_info(reset(array_keys($results['node'])));
  return $site_info;
}

/**
 * A callback to load site info for a node id.
 *
 * @param $nid
 *   The nid of the site node to load.
 * @param $options
 *   An array of options to effect the information returned.
 *
 *  Currently supports $options['server_hostname'] to filter the returned
 *  environments to only those on a server with the given hostname.
 */
function _fetcher_services_build_site_info($nid, $options = array()) {
  $site = entity_metadata_wrapper('node', node_load($nid));
  $site_info = array();
  $site_info['name'] = $site->field_ftchr_machine_name->value();
  $site_info['title'] = $site->title->value();
  $site_info['vcs'] = drupal_strtolower(_fetcher_services_get_list_display_value('field_ftchr_site_vcs', $site->field_ftchr_site_vcs->value()));
  $site_info['code_fetcher.config']['url'] = $site->field_ftchr_site_vcs_url->value();

  foreach ($site->field_ftchr_environment->value() as $environment) {
    $data = array();
    $environment = entity_metadata_wrapper('field_collection_item', $environment);
    $server = null;
    if ($environment->field_ftchr_server->value()) {
      $server = entity_metadata_wrapper('node', $environment->field_ftchr_server->value());
    }
    if (empty($server)) {
      continue;
    }
    if (_fetcher_services_check_environment_for_inclusion($environment, $options, $server)) {
      if ($environment->field_field_ftchr_vcs_rootsubdir->value()) {
        $data['webroot_subdirectory'] = $environment->field_field_ftchr_vcs_rootsubdir->value();
      }
      if ($environment->field_ftchr_branch->value()) {
        $data['code_fetcher.config']['branch'] = $environment->field_ftchr_branch->value();
      }
      if ($environment->field_ftchr_server->value()) {
        $data['remote-host'] = $server->field_ftchr_remote_host->value();
        $data['remote-user'] = $server->field_ftchr_remote_user->value();
      }
      $data['uri'] = $environment->field_ftchr_uri->value();
      $data['site.working_directory'] = $environment->field_ftchr_working_dir->value() ? $environment->field_ftchr_working_dir->value() : '/var/www/' . $site_info['name'];
      $data['root'] = $environment->field_ftchr_root->value() ? $environment->field_ftchr_root->value() : $data['site.working_directory'] . '/webroot';
      $data['version'] = _fetcher_services_get_list_display_value('field_ftchr_drupal_version', $environment->field_ftchr_drupal_version->value());
      $data['site.processes'] = $environment->field_ftchr_site_processes->value();
      $site_info['environments'][$environment->field_ftchr_environment_name->value()] = $data;
    }
  }
  array_walk_recursive($site_info, '_fetcher_services_services_trim');
  // Alter hook.
  drupal_alter('fetcher_services_site_info', $site_info);
  return $site_info;
}

/**
 * Check filters to see whether this envrionment should be included.
 */
function _fetcher_services_check_environment_for_inclusion(EntityMetadataWrapper $environment, $options, EntityMetadataWrapper $server) {

  // Without filter criteria default to returning everything.
  $include = TRUE;
  if (!empty($options['server_hostname']) || !empty($options['server_ip_address'])) {

    // Default to excluding for these filters.
    $include = FALSE;

    // If we are filtering by server and do not have one, exclude this item.
    if (!$server) {
      return FALSE;
    }
    if (!empty($options['server_hostname']) && $server->field_ftchr_remote_host->value() == $options['server_hostname']) {
      $include = TRUE;
    }
    $addresses = $server->field_ftchr_server_ip->value();
    if (!empty($options['server_ip_address']) && in_array($options['server_ip_address'], $addresses)) {
      $include = TRUE;
    }
  }
  return $include;
}

/**
 * Returns the display value for a list field.
 *
 * @param $field
 *  The name of the field (e.g. `field_foo`).
 * @param $value
 *  The actual value of the field.
 */
function _fetcher_services_get_list_display_value($field, $value) {
  $field_info = field_info_field($field);
  if (isset($field_info['settings']['allowed_values'][$value])) {
    return $field_info['settings']['allowed_values'][$value];
  }
  else {
    return FALSE;
  }
}

/**
 * Services 'alter_controllers' callback.
 *
 * @param $settings
 *   Settings for this authentication module.
 * @param $methods
 *   The methods available for the end point we're configuring.
 * @param $controller
 *   The server controller that we're configuring.
 */
function _fetcher_services_services_authentication_alter_methods($settings, &$methods, &$controller) {
  // If we're enabled for a method we need to get ssh params in the
  // request because we allow authenticating per request.
  foreach ($methods as &$method) {
    $method['args'][] = array(
      'name' => '_fetcher_services_ssh_plaintext',
      'type' => 'string',
      'description' => 'Plaintext representation of the text to sign for asymetric SSH key authentication.',
      'source' => array(
        'param' => 'ssh_plaintext',
      ),
      'optional' => TRUE,
      'default value' => '',
    );
    $method['args'][] = array(
      'name' => '_fetcher_services_ssh_signature',
      'type' => 'string',
      'description' => 'Signed representation of the text to sign for asymetric SSH key authentication.',
      'source' => array(
        'param' => 'ssh_signature',
      ),
      'optional' => TRUE,
      'default value' => '',
    );
    $method['args'][] = array(
      'name' => '_fetcher_services_ssh_fingerprint',
      'type' => 'string',
      'description' => 'The ssh fingerprint of the public key to use.',
      'source' => array(
        'param' => 'ssh_fingerprint',
      ),
      'optional' => TRUE,
      'default value' => '',
    );
  }
}

/**
 * Authenticates a call using a signed data and a public key.
 *
 * @param array $settings
 *  The settings for the authentication module.
 * @param array $method
 *  The method that's being called
 * @param array $args
 *  The arguments that are being used to call the method
 * @return void|string
 *  Returns nothing, or a error message if authentication fails
 */
function _fetcher_services_services_authentication_authenticate_call($settings, $method, $args) {

  // The authentication plugin stuff for services is half brain-dead so we have
  // to jump through crazy hoops here.

  // $args is a list of args pulled from url arguments and parameters, loop
  //through trying to find ours.

  $ssh_data = array();
  foreach ($args as $key => $value) {
    // $method is a description of whatever is being executed.  We will have
    // added params to this method description in
    // `_fetcher_services_services_authentication_alter_methods` but we have no way
    // of knowing what position ours will be in the array (because other modules
    // might have monkeyed with this module too, so loop through finding ours
    // (which are carefully namespaced) and add them to an array for our use
    // (removing the namespacing for convenience).
    if (isset($method['args'][$key]['name']) && $name = $method['args'][$key]['name']) {
      if (strpos($name, '_fetcher_services') === 0 && $value != '') {
        // Strip our namespacing for convenience and reinstate our base64
        // provided +'s, they shouldn't be spaces.
        $ssh_data[substr($name, 22)] = str_replace(' ', '+', $value);
      }
    }
  }
  try {
    $cache_key = substr(base64_decode($ssh_data['plaintext']), 0, 80);
    // If we're missing anything report it as an error.
    if (!$value = cache_get($cache_key, 'cache_fetcher_services_auth')) {
      throw new Exception(t('The plaintext key was not recognized and has either expired or was not created by this system.'));
    }
    cache_clear_all($cache_key, 'cache_fetcher_services_auth');
    if (!isset($ssh_data['fingerprint']) || !isset($ssh_data['plaintext']) || !isset($ssh_data['signature'])) {
      // An SSH parameter is missing, we just will not auth.
      throw new Exception('SSH Fingerprint not set.');
    }
    if (!$public_key = sshkey_load_by_fingerprint(base64_decode($ssh_data['fingerprint']))) {

      throw new Exception(t('SSH Key with fingerprint @fingerprint was not found', array('@fingerprint' => base64_decode($ssh_data['fingerprint']))));
    }
    if ($public_key->entity_type != 'user') {
      throw new Exception(t('SSH Key with fingerprint %fingerprint was found, but associated with a %entity_type rather than a user.', array('%fingerprint' => $ssh_data['fingerprint'], '%entity_type' => $public_key->entity_type)));
    }
    $pem_key = _fetcher_services_convert_openssh_to_pem($public_key->value);
    $key_id = openssl_get_publickey($pem_key);
    if ($key_id === FALSE) {
      throw new Exception(t('The public key could not be parsed, perhaps it is in the wrong format?'));
    }
    // Verify that the source was properly signed.
    $plain_text = base64_decode($ssh_data['plaintext']);
    // We prevent replay attacks by including a timestamp in the plaintext
    // message.  We never accept any request that's older than the number
    // of seconds in the fetcher_request_age variable.
    $signature = base64_decode($ssh_data['signature']);
    $success = openssl_verify(base64_decode($ssh_data['plaintext']), base64_decode($ssh_data['signature']), $pem_key);
    if ($success == TRUE) {
      $account = user_load($public_key->entity_id);
      global $user;
      $user = $account;
    }
    else {
      throw new Exception(t('The key on file does not appear to correspond to the one used to sign this data.'));
    }
  }
  catch (Exception $e) {
    watchdog('debug', $e->getMessage());
    return $e->getMessage();
  }
}

/**
 * Convert an OpenSSh formatted RSA key to an OpenSSL formatted key.
 *
 * @param $key
 *   The plaintext representation of the SSH key.
 */
function _fetcher_services_convert_openssh_to_pem($key) {

  list(,$data) = explode(' ', trim($key), 3);
  $data = base64_decode($data);

  list(,$algorithm_length) = unpack('N', substr($data, 0, 4));
  $algorithm = substr($data, 4, $algorithm_length);

  if ($algorithm !== 'ssh-rsa') {
      return FALSE;
  }

  list(,$e_len) = unpack('N', substr($data, 4 + strlen($algorithm), 4));
  $e = substr($data, 4 + strlen($algorithm) + 4, $e_len);
  list(,$n_len) = unpack('N', substr($data, 4 + strlen($algorithm) + 4 + strlen($e), 4));
  $n = substr($data, 4 + strlen($algorithm) + 4 + strlen($e) + 4, $n_len);

  // Algorithm identifier (id, null).
  $algorithm_id = pack('H*', '06092a864886f70d0101010500');
  // Wrap it into sequence.
  $algorithm_id = pack('Ca*a*', 0x30, _fetcher_services_key_length($algorithm_id), $algorithm_id);
  // numbers
  $data = pack('Ca*a*Ca*a*', 0x02, _fetcher_services_key_length($n), $n, 0x02, _fetcher_services_key_length($e), $e);
  // Wrap it into sequence.
  $data = pack('Ca*a*', 0x30, _fetcher_services_key_length($data), $data);
  // Don't know why, but needed.
  $data = "\x00" . $data;
  // Wrap it into sequence.
  $data = pack('Ca*a*', 0x03, _fetcher_services_key_length($data), $data);
  // Prepend the algorithm_id.
  $data = $algorithm_id . $data;
  // Wrap it into sequence.
  $data = pack('Ca*a*', 0x30,_fetcher_services_key_length($data), $data);

  $pem_key = "-----BEGIN PUBLIC KEY-----\n";
  $pem_key .= chunk_split(base64_encode($data), 64, "\n");
  $pem_key .= "-----END PUBLIC KEY-----\n";
  return $pem_key;
}

function _fetcher_services_key_length($string) {
  $length = strlen($string);
  if ($length < 0x80) {
      return chr($length);
  }
  $data = dechex($length);
  $data = pack('H*', (strlen($data) & 1 ? '0' : '') . $data);
  return chr(strlen($data) | 0x80) . $data;
}

