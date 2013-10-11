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
  $sites = array();
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'fetcher_site')
    ->fieldOrderBy('field_ftchr_machine_name', 'value')
    ->range($page, 100);
  if ($name != '') {
    $query->fieldCondition('field_ftchr_machine_name', 'value', $name, 'CONTAINS');
  }
  if ($server_hostname) {
    $ids = fetcher_services_services_get_environment_ids_from_server_hostname($server_hostname);
    $query->fieldCondition('field_ftchr_environment', 'value', $ids);
  }
  // TODO: Add optional $server param.
  $results = $query->execute();
  $nodes = node_load_multiple(array_keys($results['node']));
  $sites = array();
  foreach ($nodes as $nid => $node) {
    if ($detail) {
      $options = array();
      if ($server_hostname) {
        $options['server_hostname'] = $server_hostname;
      }
      $site = _fetcher_services_build_site_info($nid, $options);
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
    if (empty($options['server_hostname']) ||  ($server && $server->field_ftchr_remote_host->value() == $options['server_hostname'])) {
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
      $data['root'] = $environment->field_ftchr_root->value() ? $environment->field_ftchr_root->value() : '/var/www/' . $site_info['name'] . '/webroot';
      $data['version'] = _fetcher_services_get_list_display_value('field_ftchr_drupal_version', $environment->field_ftchr_drupal_version->value());
      $site_info['environments'][$environment->field_ftchr_environment_name->value()] = $data;
    }
  }
  array_walk_recursive($site_info, '_fetcher_services_services_trim');
  // Alter hook.
  drupal_alter('fetcher_services_site_info', $site_info);
  return $site_info;
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
    // (whcih are carefully namespaced) and add them to an array for our use
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

