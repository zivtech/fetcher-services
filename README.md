# Fetcher Services

https://www.drupal.org/project/fetcher_services

Fetcher Services is a Drupal module you can use to record information about all the sites and servers you or your company manage. 
In combination with [Drush Fetcher](https://www.drupal.org/project/fetcher) you and your team can access this info to easily spin up new copies of sites.

For example, if your agency is involved in 50 different projects and you have 10 developers, you want it to be easy for a developer to onramp onto a project. You can't spend 2 hours onramping someone to just do a small support request. 
You can add Fetcher Services to your intranet and keep track of all your servers, sites, and their various environments there. Then to onramp a developer, they simply use Drush Fetcher to 'fetch' a working local site with a single command.

## What's in the box

- Content types for 'Fetcher Server' and 'Fetcher Site'
- Views displays that list all your Fetcher Servers and Fetcher Sites
- A drush command for running Drupal cron jobs on sites managed with Fetcher Services
- A Services-module API for Drush Fetcher to access info from Fetcher Services
- Authentication by SSH key for the services

## Installation
```
drush dl fetcher_services
drush en fetcher_services
```
Fetcher Services has several dependencies (see `fetcher_services.info`. Note that rest_server is a submodule of `services`.)

## Assumptions

Fetcher Services assumes you use git and can run drush commands on your servers. 
It works fine with Acquia hosting, Pantheon, or your own servers.

## Usage

### Adding a site
Each of the sites you work on may have multiple environments which may be on different servers.
First add the Fetcher Servers you will need for the site, by adding a node of type 'Fetcher Server'.
Then add a node of type 'Fetcher Site', filling in each environment you have.

You can see lists of your Fetcher Servers and Sites under /admin/reports.

## Connecting with Drush Fetcher
Make sure you add an SSH key for your account at the SSH Keys tab on /user.

Add this to your drushrc.php file to connect a machine with your Fetcher Services site.

$options['fetcher']['info_fetcher.class'] = 'FetcherServices\InfoFetcher\FetcherServices';
$options['fetcher']['info_fetcher.config'] = array('host' => 'http://yoursite.com');

## Documentation
http://fetcher.readthedocs.org/en/7.x-1.x/

## Development

Development happens in Github: https://github.com/zivtech/fetcher-services
Issues and Pull Requests accepted

