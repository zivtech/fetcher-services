<?php

/**
 * @file
 *  Provides no authentication mechanism, strict passthrough.
 *
 * This is useful for using the special REST callback endpoint for
 * listing sites on a server by IP address.
 */

namespace FetcherServices\Authentication;

class None implements \Fetcher\Authentication\AuthenticationInterface {

  /**
   * Recieve a client object similar to \Fetcher\Utility\HTTPClient() and add authentication parameters.
   *
   * @param $client
   *   An HTTPClient descended object.
   * @return Void
   */
  public function addAuthenticationToHTTPClientFromDrushContext(\Fetcher\Utility\HTTPClient $client) {
  }

}
