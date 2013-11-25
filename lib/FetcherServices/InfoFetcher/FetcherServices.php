<?php

namespace FetcherServices\InfoFetcher;
use Fetcher\InfoFetcher\InfoFetcherInterface;
use Fetcher\Site;
use Fetcher\Exception\FetcherException;

class FetcherServices implements InfoFetcherInterface {

  public function __construct(Site $site) {

    // Set our default fetcher client class to our own HTTPClient.
    if (!isset($site['fetcher client class'])) {
      $site['fetcher client class'] = '\Fetcher\Utility\HTTPClient';
    }

    // Set our default fetcher client authentication class to our own HTTPClient.
    if (!isset($site['client.authentication class'])) {
      $site['client.authentication class'] = '\FetcherServices\Authentication\OpenSshKeys';
    }

    $site['client.authentication'] = $site->share(function($c) {
      return new $c['client.authentication class']($c);
    });

    $site['fetcher client'] = function($c) {
      if (!$c['info_fetcher.config']) {
        $message = 'In order to use fetcher_services the server option must be set in `$options[\'fetcher\'][\'info_fetcher.class\']`, we recommend setting it in your .drushrc.php file.';
        drush_log(dt($message), 'error');
        throw new FetcherException($message);
      }
      $client = new $c['fetcher client class']();
      $client->setURL($c['info_fetcher.config']['host'])
        ->setMethod('GET')
        ->setTimeout(3)
        ->setEncoding('json');

      // Populate this object with the appropriate authentication credentials.
      $c['client.authentication']->addAuthenticationToHTTPClientFromDrushContext($client);

      return $client;
    };
    $this->site = $site;

  }

  /**
   * List all sites.
   */
  public function listSites($name = '', $page = 0, $options = array()) {
    $client = $this->site['fetcher client'];
    $client->setPath('fetcher/api/site.json');

    // If we have a name to search for add it to the query.
    if ($name != '') {
      $client->addParam('name', $name);
    }
    // If we are paging past the first 100 results, add the page.
    if ($page) {
      $client->addParam('page', $page);
    }

    if (!empty($options)) {
      foreach ($options as $param => $value) {
        $client->addParam($param, $value);
      }
    }

    // Execute the request and decode the response.
    $result = $client->fetch();
    if (is_object($result)) {
      if (!count($result)) {
        $this->site['log']('No sites appear to exist on the server.', 'ok');
      }
      else {
        $arrayify = function ($object) use (&$arrayify) {
          if (is_object($object)) {
            foreach ($object as &$item) {
              if (is_object($item)) {
                $item = $arrayify($item);
              }
            }
          }
          return (array) $object;
        };
        return $arrayify($result);
      }
    }
    else {
      drush_log(dt('The data could not be retrieved from the server. Error code @code received from server.', array('@code' => $client->getResponseCode())), 'error');
    }
  }

  public function getInfo($site_name) {
    $client = $this->site['fetcher client'];
    $result = $client
      ->setPath("fetcher/api/site/$site_name.json")
      ->fetch();
    if ($result === FALSE) {
      $code = $client->getResponseCode();
      if ($code == 401) {
        // If access was denied, lets provide the server message for a hint as to why.
        $meta = $client->getMetadata();
        // The response code should be the first line in the response.
        if (isset($meta['wrapper_data'][0])) {
          $code = $meta['wrapper_data'][0];
          $parts = explode(' ', $code);
          // Remove the protocol and code leaving the message.
          array_shift($parts);
          array_shift($parts);
          $message = implode(' ', $parts);
          drush_log(dt('Server message: @message', array('@message' => $message)), 'error');
        }
        drush_log(dt('Access was denied, please check your authentication credentials.'), 'error');
      }
      else if ($code == 404 || $code == 200) {
        drush_log(dt('The requested site could not be found on the server.'), 'error');
      }
      else {
        drush_log(dt('The data could not be retrieved from the server. Error code @code received rom server.', array('@code' => $code)), 'error');
      }
      return FALSE;
    }
    $arrayify = function ($object) use (&$arrayify) {
      if (is_object($object)) {
        foreach ($object as &$item) {
          if (is_object($item)) {
            $item = $arrayify($item);
          }
        }
      }
      return (array) $object;
    };
    $result = $arrayify($result);
    $environments = $result['environments'];
    foreach ($result['environments'] as &$environment) {
      if (!empty($environment['code_fetcher.config'])  && !empty($result['code_fetcher.config'])) {
        // Fetcher services puts the vcs repo on the site and branch on the specific environment.
        $environment['code_fetcher.config'] = $environment['code_fetcher.config'] + $result['code_fetcher.config'];
      }
    }
    return $result;
  }

}
