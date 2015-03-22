<?php
/**
 * @file
 * Preprocess entities functions
 */


function zf_notes_preprocess_node_note__listing(&$variables){
  $node = &$variables['node'];
  $content = &$variables['content'];
  $_html = &$variables['_html'];
  $_data = &$variables['_data'];
  
  $_html['title'] = $node->title;
  $_html['message'] = drupal_render($content['field_message']);
  $category = field_get_items('node', $node, 'field_category');          
  $_html['category'] = $category[0]['taxonomy_term']->name;
  //$_html['category'] = drupal_render($content['field_category']);
  $rate = field_get_items('node', $node, 'field_rate');          
  $_html['rate'] = $rate[0]['taxonomy_term']->name;
  $_html['end_date'] = drupal_render($content['field_end_date']);
}