<?php
/**
 * @file
 * Panels pane to display the smart search form
 */

$plugin = array(
  'title' => t('Ting smart search form'),
  'description' => t("Display the smart search form"),
  'single' => TRUE,
  'content_types' => array('smart_search_string'),
  'render callback' => 'ting_smart_search_form_content_type_render',
  'access callback' => 'ting_smart_search_form_content_type_access',
  'category' => t('Ting'),
  'render last' => TRUE,
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
);

function ting_smart_search_form_content_type_access() {
  $return = FALSE;
//dpm('Inside access check');
  if (user_has_role(3) || user_has_role(5)) {
    $return = TRUE;
  }
  return $return;
}

/**
 * Render the smart search form block.
 */
function ting_smart_search_form_content_type_render($subtype, $conf, $panel_args, $context) {
    if(ting_smart_search_form_content_type_access())
    {
        // make search results sortable
        drupal_add_js('https://code.jquery.com/ui/1.12.1/jquery-ui.js');
        drupal_add_js(drupal_get_path('module', 'ting_smart_search') .'/js/smart_search_sortable.js', 'file');
        drupal_add_js(drupal_get_path('module', 'ting_smart_search') .'/js/smart_search_sortable_clear.js', 'file');

        // Create a form with options for the editors
        $form_state = array();
        $search_string = $context->data;
      //dpm($context);
        $entity_type_name = 'ting_type';
        $entity_bundle_name = 'smart_search_string';
        module_load_include('inc', 'eck', 'eck.entity');
        // Create the block class.
        $block = new stdClass();

        $entity_id = db_query('SELECT id FROM {eck_ting_type} WHERE title = :myredirect', array(':myredirect' => $search_string))->fetchField();

        if($entity_id) {
          $block->content = eck__entity__edit($entity_type_name, $entity_bundle_name, $entity_id);
        } else {
            $block->content = eck__entity__add($entity_type_name, $entity_bundle_name);
          }

        return $block;
    }
}
