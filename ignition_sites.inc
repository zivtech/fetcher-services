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
function _ignition_sites_services_index_sites($page, $name) {
  $sites = array();
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ignition_site')
    ->range($page, 100);
  if ($name != '') {
    $query = $query->fieldCondition('field_machine_name', 'value', $name, 'CONTAINS');
  }
  // TODO: Add optional $server param.
  $results = $query->execute();
  $nodes = node_load_multiple(array_keys($results[node]));
  $sites = array();
  foreach ($nodes as $nid => $node) {
    $site = entity_metadata_wrapper('node', $node);
    $sites[$site->field_machine_name->value()] = array(
      'title' => $site->title->value(),
      // TODO: add client reference.
      //'client' => $site->
    );
  }
  $trimmer = function(&$name, &$value) {
    $name = trim($name);
    if (is_string($value)) {
      $value = trim($value);
    }
  };
  array_walk($sites, $trimmer);
  return $sites;
}

/**
 * Callback for listing info about a single site.
 *
 * @param $name
 *   The name of the site to list.
 * @param $parameters
 *   An array of parameters from the services request.
 */
function _ignition_sites_services_retrieve_site($name, $parameters) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ignition_site')
    // TODO: rename this site machine name since it has to be unique
    ->fieldCondition('field_machine_name', 'value', $name, '=')
    ->range($page, 50);
  $results = $query->execute();
  $site = entity_metadata_wrapper('node', node_load(reset(array_keys($results['node']))));
  $site_info = array();
  $site_info['name'] = $site->field_machine_name->value();
  $site_info['title'] = $site->title->value();
  $site_info['nid'] = $site->nid->value();
  $site_info['vcs'] = drupal_strtolower(_ignition_sites_get_list_display_value('field_site_vcs', $site->field_site_vcs->value()));
  $site_info['vcs_url'] = $site->field_site_vcs_url->value();
  // TODO: look up real values.
  $site_info['version'] = drupal_strtolower(_ignition_sites_get_list_display_value('field_site_drupal_version', $site->field_site_drupal_version->value()));
  $site_info['support'] = (boolean) $site->field_support->value();
  $site_info['private files'] = (boolean) $site->field_private_files->value();
  foreach ($site->field_environment->value() as $environment) {
    $environment = entity_metadata_wrapper('field_collection_item', $environment);
    $data = array();
    $server = entity_metadata_wrapper('node', $environment->field_server->value());
    $name = $server->field_server_machine_name->value();
    $data['server']['name'] = $name;
    $data['server']['hostname'] = $server->field_server_hostname->value();
    // TODO: make this smart.
    $data['code hosts'][]['name'] = $name;
    $data['code hosts'][]['hostname'] = $server->field_server_hostname->value();
    $data['files host']['name'] = $name;
    $data['files host']['hostname'] = $server->field_server_hostname->value();
    $data['mysql host']['name'] = $name;
    $data['mysql host']['hostname'] = $name;
    $data['server']['hostname'] = $server->field_server_hostname->value();
    $site_info['environments'][$environment->field_environment_name->value()] = $data;
  }
  $trimmer = function(&$name, &$value) {
    $name = trim($name);
    if (is_string($value)) {
      $value = trim($value);
    }
  };
  array_walk_recursive($site_info, $trimmer);
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
function _ignition_sites_get_list_display_value($field, $value) {
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
function _ignition_sites_services_authentication_alter_methods($settings, &$methods, &$controller) {
  // If we're enabled for a method we need to get ssh params in the
  // request because we allow authenticating per request.
  foreach ($methods as &$method) {
    $method['args'][] = array(
      'name' => '_ignition_sites_ssh_plaintext',
      'type' => 'string',
      'description' => 'Plaintext representation of the text to sign for asymetric SSH key authentication.',
      'source' => array(
        'param' => 'ssh_plaintext',
      ),
      'optional' => TRUE,
      'default value' => '',
    );
    $method['args'][] = array(
      'name' => '_ignition_sites_ssh_signature',
      'type' => 'string',
      'description' => 'Signed representation of the text to sign for asymetric SSH key authentication.',
      'source' => array(
        'param' => 'ssh_signature',
      ),
      'optional' => TRUE,
      'default value' => '',
    );
    $method['args'][] = array(
      'name' => '_ignition_sites_ssh_fingerprint',
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
function _ignition_sites_services_authentication_authenticate_call($settings, $method, $args) {

  // The authentication plugin stuff for services is half brain-dead so we have
  // to jump through crazy hoops here.

  // $args is a list of args pulled from url arguments and parameters, loop
  //through trying to find ours.

  $ssh_data = array();
  foreach ($args as $key => $value) {
    // $method is a description of whatever is being executed.  We will have
    // added params to this method description in
    // `_ignition_sites_services_authentication_alter_methods` but we have no way
    // of knowing what position ours will be in the array (because other modules
    // might have monkeyed with this module too, so loop through finding ours
    // (whcih are carefully namespaced) and add them to an array for our use
    // (removing the namespacing for convenience).
    if (isset($method['args'][$key]['name']) && $name = $method['args'][$key]['name']) {
      if (strpos($name, '_ignition_sites') === 0 && $value != '') {
        // Strip our namespacing for convenience and reinstate our base64
        // provided +'s, they shouldn't be spaces.
        $ssh_data[substr($name, 20)] = str_replace(' ', '+', $value);
      }
    }
  }
  try {
    // If we're missing anything report it as an error.
    if (!isset($ssh_data['fingerprint']) || !isset($ssh_data['plaintext']) || !isset($ssh_data['signature'])) {
      // An SSH parameter is missing, we just will not auth.
      return;
    }
    if (!$public_key = sshkey_load_by_fingerprint(base64_decode($ssh_data['fingerprint']))) {

      throw new Exception(t('SSH Key with fingerprint %fingerprint was not found', array('%fingerprint' => $ssh_data['fingerprint'])));
    }
    if ($public_key->entity_type != 'user') {
      watdog('test', t('SSH Key with fingerprint %fingerprint was found, but associated with a %entity_type rather than a user.', array('%fingerprint' => $ssh_data['fingerprint'], '%entity_type' => $public_key->entity_type)));
      throw new Exception(t('SSH Key with fingerprint %fingerprint was found, but associated with a %entity_type rather than a user.', array('%fingerprint' => $ssh_data['fingerprint'], '%entity_type' => $public_key->entity_type)));
    }
    $pem_key = _ignition_sites_convert_openssh_to_pem($public_key->value);
    $key_id = openssl_get_publickey($pem_key);
    if ($key_id === FALSE) {
      throw new Exception(t('The public key could not be parsed, perhaps it is in the wrong format?'));
    }
    // Verify that the source was properly signed.
    $plain_text = base64_decode($ssh_data['plaintext']);
    // We prevent replay attacks by including a timestamp in the plaintext
    // message.  We never accept any request that's older than the number
    // of seconds in the ignition_request_age variable.
    $time = substr($plain_text, -10);
    // TODO: Provide user configuration for this variable?
    if ($time < REQUEST_TIME - variable_get('ignition_request_age', 1)) {
      throw new Exception(t('Request signature was too old.'));
    }
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
    return $e->getMessage();
  }
}

/**
 * Convert an OpenSSh formatted RSA key to an OpenSSL formatted key.
 *
 * @param $key
 *   The plaintext representation of the SSH key.
 */
function _ignition_sites_convert_openssh_to_pem($key) {

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
  $algorithm_id = pack('Ca*a*', 0x30, _ignition_sites_key_length($algorithm_id), $algorithm_id);
  // numbers
  $data = pack('Ca*a*Ca*a*', 0x02, _ignition_sites_key_length($n), $n, 0x02, _ignition_sites_key_length($e), $e);
  // Wrap it into sequence.
  $data = pack('Ca*a*', 0x30, _ignition_sites_key_length($data), $data);
  // Don't know why, but needed.
  $data = "\x00" . $data;
  // Wrap it into sequence.
  $data = pack('Ca*a*', 0x03, _ignition_sites_key_length($data), $data);
  // Prepend the algorithm_id.
  $data = $algorithm_id . $data;
  // Wrap it into sequence.
  $data = pack('Ca*a*', 0x30,_ignition_sites_key_length($data), $data);

  $pem_key = "-----BEGIN PUBLIC KEY-----\n";
  $pem_key .= chunk_split(base64_encode($data), 64, "\n");
  $pem_key .= "-----END PUBLIC KEY-----\n";
  return $pem_key;
}

function _ignition_sites_key_length($string) {
  $length = strlen($string);
  if ($length < 0x80) {
      return chr($length);
  }
  $data = dechex($length);
  $data = pack('H*', (strlen($data) & 1 ? '0' : '') . $data);
  return chr(strlen($data) | 0x80) . $data;
}

