<?php

class MKSXmlMigration extends XMLMigration{
  protected $level;
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Namespaced XML feed of wine producers of the world');
    
    $fields = array(
      'title' => t('Title'),      
      'coursecode' => t('Course code'),
      'level' => t('Level'),
      'subject' => t('Subject'),
      'clearingstatus' => ('status')
    );
    
    $xml_folder = DRUPAL_ROOT . '/' .
                  drupal_get_path('module', 'tst_migrate') . '/xml/';
    if (isset($this->level)){
      $list_url = $xml_folder . $this->level. '.xml';
    } 
    else {
      $list_url = $xml_folder . 'courses.xml';
    }    
    $list_xpath = '/rss/channel/item/sql:coursecode';
    $item_url = $xml_folder . ':id.xml';
    $item_xpath = '/rss/channel/item';
    
    $list = new MKSMigrateListXML($list_url, $list_xpath);
    $item = new MKSMigrateItemXML($item_url, $item_xpath);
    $this->source = new MigrateSourceList($list, $item, $fields);

    $this->destination = new MigrateDestinationNode('course');
    
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'coursecode' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->addFieldMapping('title', 'title')->xpath('title');
    $this->addFieldMapping('field_subject', 'subject');//->separator(',');
    $this->addFieldMapping('field_coursecode', 'sql:coursecode')->xpath('sql:coursecode');
    $this->addFieldMapping('field_level', 'level');    
  }
  
  public function prepareRow($row) {
    $subjects = $row->xml->xpath('sql:subjectarea');
    $subjects = (string)$subjects[0];
    $terms = preg_split("/,(?=\S)/", $subjects);
    $row->subject = $terms;
    
    $row->level = $this->level;
  }
  
  public function prepare($entity, $row) {
    //$entity->field_level['und'][0]['value'] = $this->level;
  }
  
}


class MKSXmlDataMigration extends XMLMigration{
  protected $level;
  public function __construct($arguments) {    
    parent::__construct($arguments);
    $this->description = t('Namespaced XML feed of wine producers of the world');
    $this->systemOfRecord =  Migration::DESTINATION;
    
    $fields = array(
      'sql:startdate' => t('Date'),
      'length' => t('Length')
    );
    
    //$this->dependencies = array('MKSXml');
    $xml_folder = DRUPAL_ROOT . '/' .
              drupal_get_path('module', 'tst_migrate') . '/xml/';
    if (isset($this->level)){
      $items_url = $xml_folder . $this->level. '.xml';
    } 
    else {
      $items_url = $xml_folder . 'courses.xml';
    }        
    $item_xpath = '/rss/channel/item';
    // This is the xpath relative to the individual items - thus the full xpath
    // of an ID will be /producers/producer/sourceid.
    $item_ID_xpath = 'sql:coursecode';

    $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath, ['sql' => 'http://www.rssbus.com/ns?SqlOps/v1']);
    $this->source = new MigrateSourceMultiItems($items_class, $fields);

    $this->destination = new MigrateDestinationNode('course');
    
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'coursecode' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->addFieldMapping('nid', 'coursecode')->sourceMigration($this->dependencies);
    $this->addFieldMapping('field_length', 'length')->xpath('sql:length');
    $this->addFieldMapping('field_startdate', 'startdate')->xpath('sql:startdate');       
  }
  public function prepareRow($row) {
    //dpm($row);
    $date = $row->xml->xpath('sql:startdate')[0];
    $date = (string)$date;
    list($day, $month, $year) = explode('/', $date);
    $row->startdate = implode('/', array($month, $day, $year));    
  } 
  public function prepare($entity, $row) {
    
  } 
  
}

class MKSMigrateListXML extends MigrateListXML{
  
  protected $xpath;
  
  public function __construct($list_url, $xpath='/', array $namespaces = array()) {
    parent::__construct($list_url, $namespaces);
    $this->xpath = $xpath;
  }  
  
  protected function getIDsFromXML(SimpleXMLElement $xml) {
    $ids = array();
    $xml = $xml->xpath($this->xpath);
    foreach ($xml as $element) {
      $ids[] = (string) $element;
    }
    // Additionally, if there are any namespaces registered, try to parse
    // elements with namespaces as well.

    return array_unique($ids);
  }
  
}

class MKSMigrateItemXML extends MigrateItemXML{
  
  protected $xpath;
  
  public function __construct($item_url, $xpath='/', array $namespaces = array()) {
    parent::__construct($item_url, $namespaces);
    $this->xpath = $xpath;
  }
  
  protected function loadXmlUrl($item_url) {
    $xml = simplexml_load_file($item_url);
    if($xml){
      return $xml->xpath($this->xpath)[0];
    }
  }
  
  
}

class MKSXmlUGMigration extends MKSXmlMigration {
  public function __construct($arguments) {
    $this->level = 'UG';
    parent::__construct($arguments);
    $this->description = t('UG');
  }
}
class MKSXmlUGDataMigration extends MKSXmlDataMigration {
  public function __construct($arguments) {
    $this->level = 'UG';
    $this->dependencies = array('MKSXmlUG');
    parent::__construct($arguments);
    $this->description = t('UG');
  }
}

class MKSXmlPGMigration extends MKSXmlMigration {
  public function __construct($arguments) {
    $this->level = 'PG';
    parent::__construct($arguments);
    $this->description = t('PG');
  }
}
class MKSXmlPGDataMigration extends MKSXmlDataMigration {
  public function __construct($arguments) {
    $this->level = 'PG';
    $this->dependencies = array('MKSXmlPG');
    parent::__construct($arguments);
    $this->description = t('PG');
  }
}

class MKSXmlFCMigration extends MKSXmlMigration {
  public function __construct($arguments) {
    $this->level = 'FC';
    parent::__construct($arguments);
    $this->description = t('FC');
  }
}
class MKSXmlFCDataMigration extends MKSXmlDataMigration {
  public function __construct($arguments) {
    $this->level = 'FC';
    $this->dependencies = array('MKSXmlFC');
    parent::__construct($arguments);
    $this->description = t('FC');
  }
}

class MKSXmlCLMigration extends XmlMigration {
  protected $processed_before;
  protected $all_dest;
  public function __construct($arguments) {    
    parent::__construct($arguments);
    $this->description = t('Namespaced XML feed of wine producers of the world');
    $this->systemOfRecord =  Migration::DESTINATION;
    $this->dependencies = array('MKSXmlFC', 'MKSXmlUG', 'MKSXmlPG');
    
    $fields = array(
      'clear_mode' => t('Date'),
      'coursecode' => t('NID')
    );
    
    //$this->dependencies = array('MKSXml');
    $xml_folder = DRUPAL_ROOT . '/' .
              drupal_get_path('module', 'tst_migrate') . '/xml/';

    $items_url = $xml_folder . 'CL.xml';    
    $item_xpath = '/rss/channel/item';
    // This is the xpath relative to the individual items - thus the full xpath
    // of an ID will be /producers/producer/sourceid.
    $item_ID_xpath = 'sql:coursecode';

    $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath, ['sql' => 'http://www.rssbus.com/ns?SqlOps/v1']);
    $this->source = new MigrateSourceMultiItems($items_class, $fields);

    $this->destination = new MigrateDestinationNode('course');
    
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'coursecode' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );
    $this->addFieldMapping('nid', 'coursecode')->sourceMigration($this->dependencies);
    $this->addFieldMapping('field_clear_mode', 'clear_mode');   
  }
  public function prepareRow($row) {
    //dpm($row);
    $row->clear_mode = 1;
  } 
  public function prepare($entity, $row) {
    $this->all_dest[] = $entity->nid;
    if (isset($this->processed_before[$entity->nid])){
      //unset($this->processed_before[$entity->nid]);
    }
  } 
  
  public function preImport() {
    parent::preImport();
    dpm($this->all_dest);
    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'course')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->fieldCondition('field_clear_mode', 'value', '1', '=');

    $result = $query->execute();

    if (isset($result['node'])) {
      $news_items_nids = $result['node'];
      $this->processed_before = $news_items_nids;
    }
    
  }
  public function postImport() {
    dpm($this->all_dest);
    parent::postImport();
    if (isset($this->processed_before)&&!$this->errorCount()){
      foreach ($this->processed_before as $key => $value) {
        $node = node_load($key);
        //$node->field_clear_mode['und'][0]['value'] = 0;
        node_save($node);
      }
    }
    dpm($this->processed_before);
  }
}


class MKSXmlSubjMigration extends XMLMigration{

  public function __construct($arguments) {    
    parent::__construct($arguments);
    $this->description = t('Namespaced XML feed of wine producers of the world');
    
    $fields = array(
      'title' => t('Length'),
    );
    

    $items_url = 'http://feeds.westminster.ac.uk/rssbus/pub/prospectus_subject_areas.rsb?@rss';
    $item_xpath = '/rss/channel/item';
    // This is the xpath relative to the individual items - thus the full xpath
    // of an ID will be /producers/producer/sourceid.
    $item_ID_xpath = 'guid';

    $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath);
    $this->source = new MigrateSourceMultiItems($items_class, $fields);

    $this->destination = new MigrateDestinationTerm('subjects');
    
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'guid' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
        )
      ),
      MigrateDestinationTerm::getKeySchema()
    );
    $this->addFieldMapping('name', 'title')->xpath('title');
           
  }
  
}