<?php

/**
 * @file
 *  Provides authentication
 */

namespace FetcherServices\Authentication;
use Fetcher\Exception\FetcherException;
use Fetcher\Site;
use Symfony\Component\Process\Process;

class OpenSshKeys implements \Fetcher\Authentication\AuthenticationInterface {

  private $site = NULL;

  public function __construct(Site $site) {
    $this->site = $site;
  }

  /**
   * Recieve a client object similar to \Fetcher\Utility\HTTPClient() and add authentication parameters.
   *
   * @param $client
   *   An HTTPClient descended object.
   * @return Void
   */
  public function addAuthenticationToHTTPClientFromDrushContext(\Fetcher\Utility\HTTPClient $client) {

    // TODO: Allow the specification of the key to use.

    // Generate pseudo random noise to sign for this transaction.
    // The current time is included preventing replay attacks.
    $site = $this->site;
    $textLoadingClient = new $site['fetcher client class']();
    $text = $textLoadingClient
      ->setURL($site['info_fetcher.config']['host'])
      ->setMethod('GET')
      ->setTimeout(3)
      ->setEncoding('json')
      ->setPath('fetcher-services/api/get-token')
      ->fetch();
    $data = $this->getSignatureAndFingerprint($text);

    $client->addParam('ssh_plaintext', base64_encode($text));
    $client->addParam('ssh_signature', base64_encode($data['signature']));
    $client->addParam('ssh_fingerprint', base64_encode($data['fingerprint']));

  }

  /**
   * Load the plaintext public key.
   *
   * @return
   *   A string of the OpenSSH formatted public key.
   */
  public function getPublicKey() {
    // TODO: Make this smarter/configurable.
    $system = $this->site['system'];
    $home_folder = $system->getUserHomeFolder();
    if (file_exists($home_folder . '/.ssh/id_rsa.pub')) {
      return file_get_contents($home_folder . '/.ssh/id_rsa.pub');
    }
    else {
      throw new \Exception('Key could not be located.');
    }
  }

   /**
    * Parses a SSH public key generating the fingerprint for an OpenSSH formatted public key.
    *
    * This method taken from the sshkey module http://drupal.org/project/sshkey.
    *
    * @param string $keyRaw
    *   The string with the raw SSH public key.
    */
  public function parsePublicKey($keyRaw) {
     $parsed['value'] = trim(preg_replace('/\s+/', ' ', $keyRaw));

     // The SSH key should be a string in the form:
     // "<algorithm type> <base64-encoded key> <comment>"
     $keyParts = explode(' ', $parsed['value'], 3);
     if (count($keyParts) < 2) {
       throw new Exception(dt('Fetcher Services Authentication Error: The key is invalid.'));
     }

     $parsed['algorithm'] = $keyParts[0];
     if (!in_array($parsed['algorithm'], array('ssh-rsa', 'ssh-dss'))) {
       throw new FetcherException(dt("Fetcher Services Authentication Error: The key is invalid. It must begin with <em>ssh-rsa</em> or <em>ssh-dss</em>."));
     }

     $parsed['key'] = $keyParts[1];
     $keyBase64Decoded = base64_decode($parsed['key']);
     if ($keyBase64Decoded === FALSE) {
       throw new FetcherException(dt('Fetcher Services Authentication Error: The key could not be decoded.'));
     }
     $parsed['fingerprint'] = md5($keyBase64Decoded);

     if (isset($keyParts[2])) {
       $parsed['comment'] = $keyParts[2];
     }

     return $parsed;
  }

  /**
   * Sign some text and return the signature.
   */
  public function getSignatureAndFingerprint($text) {
    // Attempt to load the signature from the ssh-agent.
    if ($this->sshAgentExists() && $signature_and_fingerprint = $this->getSignatureAndFingerprintFromSSHAgent($text)) {
      return $signature_and_fingerprint;
    }
    else {
      // ssh-agent isn't running or failed, try to use a local key.
      // Load the private key in .pem format.
      // TODO: Make this smarter/configurable.

      $keyData = $this->parsePublicKey($this->getPublicKey());
      $fingerprint = $keyData['fingerprint'];
      $process = new Process('openssl rsa -in ' . $this->site['system']->getUserHomeFolder() . '/.ssh/id_rsa');
      $process->setTimeout(3600);
      $process->run();
      if (!$process->isSuccessful()) {
        throw new \RuntimeException($process->getErrorOutput());
      }
      $pemText = $process->getOutput();
      $privateKeyId = openssl_get_privatekey($pemText);
      $signature = '';
      openssl_sign($text, $signature, $privateKeyId);
      return array('fingerprint' => $fingerprint, 'signature' => $signature);
    }
  }

  /**
   * Check to see whether ssh-agent is running on the system.
   */
  public function sshAgentExists() {
    $address = getenv('SSH_AUTH_SOCK');
    // Ensure we have an address
    if ($address && stream_socket_client('unix://' . $address)) {
      return TRUE;
    }
  }

  /**
   * Retrieve the SSH signature from ssh-agent.
   */
  public function getSignatureAndFingerprintFromSSHAgent($text) {
    // TODO: We found working python code that can communicate with ssh-agent,
    // so we're using an approach based on that code.  Everything done in python
    // has a PHP analogue and it shouldn't be too hard to write a PHP implementation
    // rather than shelling out to the included python script.
    $process = new Process('python ' . __DIR__ . '/SSHAgentCommunicator.py ' . $text);
    $process->setTimeout(3600);
    $process->run();
    if (!$process->isSuccessful()) {
      return FALSE;
    }
    $output = (array) json_decode($process->getOutput());
    $output['signature'] = base64_decode($output['signature']);
    $output['fingerprint'] = str_replace(':', '', $output['fingerprint']);
    return $output;
  }
}
