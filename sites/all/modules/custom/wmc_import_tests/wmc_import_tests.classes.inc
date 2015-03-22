<?php
/**
 * @file
 * Additional classes used in migrations.
 */

/**
 * Overriding MigrateSourceMultiItems class.
 */
class WMCMigrateSourceMultiItems extends MigrateSourceMultiItems {

  public function hash($row) {
    // Unsetting pubDate property from feed to prevent hash updates
    // as it changes every second.
    if (isset($row->xml->pubDate)) {
      unset($row->xml->pubDate);
    }
    migrate_instrument_start('MigrateSource::hash');
    $hash = md5(serialize($row->xml->asXML()));
    migrate_instrument_stop('MigrateSource::hash');

    return $hash;
  }
}

/**
 * Overriding MigrateSourceList class.
 */
class WMCMigrateSourceList extends MigrateSourceList {

  public function hash($row) {
    // Unsetting pubDate property from feed to prevent hash updates
    // as it changes every second.
    if (isset($row->xml->pubDate)) {
      unset($row->xml->pubDate);
    }
    migrate_instrument_start('MigrateSource::hash');
    $hash = md5(serialize($row->xml->asXML()));
    migrate_instrument_stop('MigrateSource::hash');

    return $hash;
  }
}

/**
 * Overriding MigrateListXML class
 */
 class WMCMigrateListXML extends MigrateListXML{

    protected $xpath;

    public function __construct($list_url, $xpath = '/', array $namespaces = array()) {
      parent::__construct($list_url, $namespaces);
      $this->xpath = $xpath;
    }

    protected function getIDsFromXML(SimpleXMLElement $xml) {
      $result = $xml->xpath($this->xpath);
      $ids = array();
      if ($result) {
        foreach ($result as $element) {
          if (!isset($element)) {
            continue;
          }
          // Namespaces must be reapplied after xpath().
          $this->registerNamespaces($element);
          $id = $element;
          if (!is_null($id)) {
            $ids[] = (string) $id;
          }
        }
      }
      return array_unique($ids);
    }

 }

 /**
  * Overriding MigrateItemXML class
  */
 class WMCMigrateItemXML extends MigrateItemXML {

  protected $xpath;

  public function __construct($item_url, $xpath = '/', array $namespaces = array()) {
    parent::__construct($item_url, $namespaces);
    $this->xpath = $xpath;
  }

  protected function loadXmlUrl($item_url) {
    $xml = simplexml_load_file($item_url);
    $result = $xml->xpath($this->xpath);
    return $result[0];
  }

  public function hash($row) {
    if (isset($row->xml->pubDate)) {
      unset($row->xml->pubDate);
    }
    migrate_instrument_start('MigrateSource::hash');
    $hash = md5(serialize($row->xml->asXML()));
    migrate_instrument_stop('MigrateSource::hash');
    return $hash;
  }

}