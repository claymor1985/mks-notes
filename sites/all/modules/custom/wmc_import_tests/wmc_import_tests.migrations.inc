<?php
/**
 * @file
 * Migration classes.
 */

/**
 * Subjects migration.
 */
class ImportWmcTestSubjectMigration extends XMLMigration {
  /**
   * A class constructor.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Imports subjects for courses from "Prospectus Subject Areas at University of Westminster" rss');

    // Source fields.
    $fields = array(
      'title' => t('Subject title'),
      'code' => t('Subject Code'),
    );

    // Define url and xpath for feed.
    $xml_folder = DRUPAL_ROOT . '/' .
          drupal_get_path('module', 'wmc_import_tests') . '/xml/';
    $items_url = $xml_folder . 'subjects.xml';

    $item_xpath = '/rss/channel/item';
    $item_ID_xpath = $this->itemIDXpath = 'guid';

    $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath);

    // Create instances of source and destination classes.
    $this->source = new WMCMigrateSourceMultiItems($items_class, $fields, array('track_changes' => TRUE));
    $this->destination = new MigrateDestinationTerm('subjects');

    // Add field mapping.
    $this->addFieldMapping('name', 'title')->xpath('title');
    $this->addFieldMapping('field_subject_code', 'code')->xpath('sql:subject_area_code');
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
  }
}

/**
 * All courses migration.
 */
class ImportWmcTestCoursesMigration extends XMLMigration {
  // Define Course level property. Used in feed url compilation.
  protected $course_level;
  protected $processed_before;
  protected $all_dest;

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Imports courses from rss');

    // Source fields.
    $fields = array(
      'title' => t('Title'),
      'course_code' => t('Course code'),
      'subject' => t('Subjects'),
      'apply_type' => t('Apply type'),
      'ucasukpasscode' => t('UCAS UK Pass code'),
      //'institution_code' => t('Institution code'),
      'faculty_name' => t('Faculty name'),
      'faculty_link' => t('Faculty site link'),
      'location' => t('Campus'),
      'homeeu_fees' => t('Home Eu Fees'),
      'overseas_fees' => t('Overseas Fees'),
      'fieldtrip_fees' => t('Field trip fees'),
      'fees_calculation_type' => t('Fees calculation type'),
      'fee_module_based' => t('Fee module based'),
      'course_level' => t('Course level'),
      'clearing_status' => t('Clearing status'),
      'vacancies_abb' => t('Vacancies ABB'),
      'vacancies_adjustment' => t('Vacancies adjustment'),
      'vacancies_home' => t('Vacancies home'),
      'vacancies_overseas' => t('Vacancies overseas'),
    );

    // Creating url of feed conatining ids for migration.
    // Class course_level property needs to be defined in constructor for each migration.
    // If it's not we can try to made all courses migration.
    $xml_folder = DRUPAL_ROOT . '/' .
              drupal_get_path('module', 'wmc_import_tests') . '/xml/';
    if (isset($this->course_level)){
      $list_url = $xml_folder . $this->course_level. '.xml';
    }
    else {
      $list_url = $xml_folder . 'courses.xml';
    }
    $ids_xpath = '/rss/channel/item/sql:coursecode';
    $item_url = $xml_folder . ':id.xml';
    $item_xpath = '/rss/channel/item';

    // Create instances of source and destination classes.
    $this->source = new WMCMigrateSourceList(new WMCMigrateListXML($list_url, $ids_xpath),
      new WMCMigrateItemXML($item_url, $item_xpath), $fields, array('track_changes' => TRUE));
    $this->destination = new MigrateDestinationNode('course');

    // Add field mapping.
    $this->addFieldMapping('title', 'title')->xpath('title');
    //$this->addFieldMapping('status', 'title')->xpath('title');
    $this->addFieldMapping('field_course_code', 'course_code')->xpath('sql:coursecode');
    $this->addFieldMapping('field_subject', 'subject');
    $this->addFieldMapping('field_apply_type', 'apply_type')->xpath('sql:applytype');
    $this->addFieldMapping('field_ucasukpasscode', 'ucasukpasscode')->xpath('sql:ucasukpasscode');
    //$this->addFieldMapping('field_institution_code', 'institution_code')->xpath('sql:campus');
    $this->addFieldMapping('field_faculty_link', 'faculty_link')->xpath('sql:facultyhomepage');
    $this->addFieldMapping('field_faculty_link:title', 'faculty_name')->xpath('sql:facultyname');
    $this->addFieldMapping('field_location', 'location')->xpath('sql:campus');
    $this->addFieldMapping('field_homeeu_fees', 'homeeu_fees')->xpath('sql:feeshomeeu');
    $this->addFieldMapping('field_overseas_fees', 'overseas_fees')->xpath('sql:feesoverseas');
    $this->addFieldMapping('field_fieldtrip_fees', 'fieldtrip_fees')->xpath('sql:feesfieldtrip');
    $this->addFieldMapping('field_fee_module_based', 'fee_module_based')->xpath('sql:feesmodulebased');
    //$this->addFieldMapping('field_fees_calculation_type', 'fees_calculation_type')->xpath('sql:feesmodulebased');
    $this->addFieldMapping('field_course_level', 'course_level');
    //$this->addFieldMapping('field_clearing_status', 'clearing_status')->xpath('sql:clearingstatus');
    $this->addFieldMapping('field_vacancies_abb', 'vacancies_abb')->xpath('sql:vacanciesabb');
    $this->addFieldMapping('field_vacancies_adjustment', 'vacancies_adjustment')->xpath('sql:vacanciesadjustment');
    $this->addFieldMapping('field_vacancies_home', 'vacancies_home')->xpath('sql:vacancieshome');
    $this->addFieldMapping('field_vacancies_overseas', 'vacancies_overseas')->xpath('sql:vacanciesoverseas');

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
  }

  /**
   * Overriding method prepareRow for row data transformations.
   */
  public function prepareRow($row) {
    global $language;

    // Prepare course_level field.
    $courses_levels = array(
      'UG' => 'Undergraduate',
      'FC' => 'Undergraduate with Foundation',
      'PG' => 'Postgraduate',
      'FD' => 'Foundation',
    );

    if (isset($this->course_level)) {
      $row->course_level = $courses_levels[$this->course_level];
    }

    //Prepare subjects field
    $subjects = $row->xml->xpath('sql:subjectarea');
    $subjects = (string)$subjects[0];
    $terms = preg_split("/,(?=\S)/", $subjects);
    $row->subject = $terms;

    // Convert field fee_module_based to boolean.
    $fee_module_based = $row->xml->xpath('sql:feesmodulebased');
    $fee_module_based = (string)$fee_module_based[0];
    $row->fee_module_based = ($fee_module_based == 'Y') ? 1 : 0;

    // Prepare location field.
    $location = $row->xml->xpath('sql:campus');
    $location = (string)$location[0];
    if (!empty($location)) {

      // Check if we already have campus node with this title.
      $view = views_get_view_result(WMC_IMPORT_VIEW_QUERY_CAMPUS_BY_TITLE, 'default', $location);
      if (!empty($view)) {
        $node = array_shift($view);
        $row->location = $node->nid;
      }
      else {

        // Create new node if doesn't exists yet.
        $node = new stdClass;
        $node->type = 'campus';
        $node->status = NODE_NOT_PUBLISHED;
        $node->language = $language->language;
        $node->title = $location;
        node_save($node);
        $row->location = $node->nid;
      }
    }
  }
}

/**
 * All courses additional data migration.
 */
class ImportWmcTestCoursesDataMigration extends XMLMigration {

  // Define Course level property. Used in feed url compilation.
  protected $course_level;

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Imports additional courses data from rss');

    // Priority for update existing nodes rather then create
    $this->systemOfRecord = Migration::DESTINATION;

    // Source fields.
    $fields = array(
      'coursecode' => t('Course code'),
      'attendance_mode' => t('Attendance mode'),
      'startdate' => t('Subject title'),
      'course_location' => t('Location'),
      'course_duration' => t('Duration'),
    );

    // Creating url of feed conatining ids for migration and items data in one feed.
    $xml_folder = DRUPAL_ROOT . '/' .
              drupal_get_path('module', 'wmc_import_tests') . '/xml/';
    if (isset($this->course_level)){
      $items_url = $xml_folder . $this->course_level. '.xml';
    }
    else {
      $items_url = $xml_folder . 'courses.xml';
    }

    // Creating instance of items class for Source class constructor.
    $item_xpath = '/rss/channel/item';
    $item_ID_xpath = $this->itemIDXpath = 'sql:coursecode';
    $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath);

    // Create instances of source and destination classes.
    $this->source = new WMCMigrateSourceMultiItems($items_class, $fields, array('track_changes' => TRUE));
    $this->destination = new MigrateDestinationNode('course');

    // Add field mapping.
    // Dependencies property must be defined for each migrate class according on requested course_level.
    if (isset($this->dependencies)) {
      $this->addFieldMapping('nid', 'coursecode')->sourceMigration($this->dependencies);
    }
    $this->addFieldMapping('field_attendance_mode', 'attendance_mode')->xpath('sql:attendancemode');
    $this->addFieldMapping('field_start_date', 'startdate');
    $this->addFieldMapping('field_start_date:timezone')->defaultvalue('Europe/London');
    $this->addFieldMapping('field_course_location', 'course_location')->xpath('sql:location');
    $this->addFieldMapping('field_course_duration', 'course_duration')->xpath('sql:length');
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
  }

  public function prepareRow($row) {

    // Prepare date row in correct format.
    $date = $row->xml->xpath('sql:startdate');
    $date = (string)$date[0];
    list($day, $month, $year) = explode('/', $date);
    $row->startdate = implode('/', array($month, $day, $year));

  }

}

/**
 *  UG courses migration.
 *  Retrieve courses for a specific level
 */
class ImportWmcTestCoursesUGMigration extends ImportWmcTestCoursesMigration{
  public function __construct($arguments) {
    $this->course_level = WMC_IMPORT_LEVEL_UDEGRATUATE;
    parent::__construct($arguments);
    $this->description = t('Imports courses  for UG level from rss');
  }
}

class ImportWmcTestCoursesUGDataMigration extends ImportWmcTestCoursesDataMigration{
  public function __construct($arguments) {
    $this->course_level = WMC_IMPORT_LEVEL_UDEGRATUATE;
    $this->dependencies = array('ImportWmcTestCoursesUG');
    parent::__construct($arguments);
    $this->description = t('Imports courses  for UG level from rss');
  }
}

/**
 *  FC courses migration.
 *  Retrieve courses for a specific level
 */
class ImportWmcTestCoursesFCMigration extends ImportWmcTestCoursesMigration{
  public function __construct($arguments) {
    $this->course_level = WMC_IMPORT_LEVEL_UDEGRATUATE_WITH_FOUNDATION;
    parent::__construct($arguments);
    $this->description = t('Imports courses  for FC level from rss');
  }
}

class ImportWmcTestCoursesFCDataMigration extends ImportWmcTestCoursesDataMigration{
  public function __construct($arguments) {
    $this->course_level = WMC_IMPORT_LEVEL_UDEGRATUATE_WITH_FOUNDATION;
    $this->dependencies = array('ImportWmcTestCoursesFC');
    parent::__construct($arguments);
    $this->description = t('Imports courses  for FC level from rss');
  }
}

/**
 *  PG courses migration.
 *  Retrieve courses for a specific level
 */
class ImportWmcTestCoursesPGMigration extends ImportWmcTestCoursesMigration{
  public function __construct($arguments) {
    $this->course_level = WMC_IMPORT_LEVEL_POSTGRADUATE;
    parent::__construct($arguments);
    $this->description = t('Imports courses  for PG level from rss');
  }
}

class ImportWmcTestCoursesPGDataMigration extends ImportWmcTestCoursesDataMigration{
  public function __construct($arguments) {
    $this->course_level = WMC_IMPORT_LEVEL_POSTGRADUATE;
    $this->dependencies = array('ImportWmcTestCoursesPG');
    parent::__construct($arguments);
    $this->dependencies = array('ImportWmcTestCoursesPG');
    $this->description = t('Imports courses  for PG level from rss');
  }
}

/**
 *  FD courses migration.
 *  Retrieve courses for a specific level
 */
class ImportWmcTestCoursesFDMigration extends ImportWmcTestCoursesMigration{
  public function __construct($arguments) {
    $this->course_level = WMC_IMPORT_LEVEL_FOUNDATION_COURSE;
    parent::__construct($arguments);
    $this->description = t('Imports courses  for FD level from rss');
  }
}

class ImportWmcTestCoursesFDDataMigration extends ImportWmcTestCoursesDataMigration{
  public function __construct($arguments) {
    $this->course_level = WMC_IMPORT_LEVEL_FOUNDATION_COURSE;
    $this->dependencies = array('ImportWmcTestCoursesFD');
    parent::__construct($arguments);
    $this->description = t('Imports courses  for FD level from rss');
  }
}


class ImportWmcTestCLMigration extends XmlMigration {
  protected $processed_before;
  protected $all_dest;
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Namespaced XML feed of wine producers of the world');
    $this->systemOfRecord =  Migration::DESTINATION;
    $this->dependencies = array('ImportWmcTestCoursesUG', 'ImportWmcTestCoursesFC', 'ImportWmcTestCoursesFD', 'ImportWmcTestCoursesPG');

    $fields = array(
      'clearing_status' => t('Clearing status'),
      'coursecode' => t('ID')
    );

    //$this->dependencies = array('MKSXml');
    $xml_folder = DRUPAL_ROOT . '/' .
              drupal_get_path('module', 'wmc_import_tests') . '/xml/';

    $items_url = $xml_folder . 'CL.xml';
    $item_xpath = '/rss/channel/item';
    // This is the xpath relative to the individual items - thus the full xpath
    // of an ID will be /producers/producer/sourceid.
    $item_ID_xpath = 'sql:coursecode';

    $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath, ['sql' => 'http://www.rssbus.com/ns?SqlOps/v1']);
    $this->source = new WMCMigrateSourceMultiItems($items_class, $fields);

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
    $this->addFieldMapping('field_clearing_status', 'clearing_status');
  }

  public function prepareRow($row) {
    //dpm($row);
    $row->clearing_status = 1;
  }

  public function prepare($entity, $row) {
    $this->all_dest[] = $entity->nid;
    if (isset($this->processed_before[$entity->nid])){
      unset($this->processed_before[$entity->nid]);
    }
  }

  public function preImport() {
    parent::preImport();
    dpm($this->all_dest);
    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'course')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->fieldCondition('field_clearing_status', 'value', '1', '=');

    $result = $query->execute();

    if (isset($result['node'])) {
      $news_items_nids = $result['node'];
      $this->processed_before = $news_items_nids;
    }

  }

  public function postImport() {
    global $language;

    dpm($this->all_dest);
    parent::postImport();
    if (isset($this->processed_before)&&!$this->errorCount()){
      foreach ($this->processed_before as $key => $value) {
        $node = node_load($key);
          $node->field_clearing_status[LANGUAGE_NONE][0]['value'] = 0;
        node_save($node);
      }
    }
    dpm($this->processed_before);
  }
}
