<?php
// $Id$

/**
 * @file armory.admin.inc
 * This file contains the admin settings functions for armory and the 
 * other included modules (guilds and characters).
 */

function armory_settings() {
  // Create the storage directories for serverlists and characters, if it does not already exist.
  $armory_dir = file_directory_path() .'/armory';
  file_check_directory($armory_dir, 1);
  $serverlist_dir = file_directory_path() .'/armory/serverlists';
  file_check_directory($serverlist_dir, 1);
  $character_dir = file_directory_path() .'/armory/characters';
  file_check_directory($character_dir, 1);
  $guild_dir = file_directory_path() .'/armory/guilds';
  file_check_directory($guild_dir, 1);

  $form['armory_settings'] = array(
    '#prefix' => '<div id="armory-admin-settings-form">',
    '#suffix' => '</div>',
  );

  $form['armory_settings']['style'] = array(
    '#type' => 'fieldset',
    '#title' => t('Armory style'),
    '#description' => t('Choose the style you want your Armory information like character sheets and guildlists to be displayed in. Plain bright fits most minimalistic bright themes like Garland or Kubrick.')
  );

  $styles = array(
    'armory-plain-bright' => t('Plain bright'),
    'armory-plain-dark' => t('Plain dark'),
  );
  $form['armory_settings']['style']['armory_style'] = array(
    '#type' => 'select',
    '#options' => $styles,
    '#default_value' => variable_get('armory_style', 'armory-plain-bright'),
  );

  $form['armory_settings']['intro'] = array(
    '#type' => 'fieldset',
    '#title' => t('Armory intro text'),
  );

  $form['armory_settings']['intro']['intro_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Intro text'),
    '#default_value' => variable_get('armory_intro_text', ARMORY_DEFAULT_INTRO),
    '#description' => t('This is the text that will be shown at the <a href="@armory" title="Go to the Warcraft Armory page on this site">Warcraft Armory</a> page.', array('@armory' => url('armory'))),
  );

  $form['armory_settings']['maxage'] = array(
    '#type' => 'fieldset',
    '#title' => t('XML-file age settings'),
  );

  $update_intervals = array(
    0 => t('Never'),
    1 => t('Always'),
    3600 => t('Every hour'),
    10800 => t('Every 3 hours'),
    21600 => t('Every 6 hours'),
    86400 => t('Every day'),
    604800 => t('Once per week'),
    2500000 => t('Once per month'),
  );

  $form['armory_settings']['maxage']['characters_maxage'] = array(
    '#type' => 'select',
    '#title' => t('Characters and guilds update interval'),
    '#description' => t('Guilds and characters are stored as xml-files fetched from the Armory. These should be updated regularly to provide your visitors and members with up-to-date information about your guild and characters.'),
    '#options' => $update_intervals,
    '#default_value' => variable_get('armory_characters_maxage', 86400),
  );

  $form['armory_settings']['maxage']['serverlist_maxage'] = array(
    '#type' => 'select',
    '#title' => t('Serverlists update interval'),
    '#description' => t('Serverlists are xml-files fetched from Blizzard. Blizzard adds servers from time to time, so these must be updated once in a while. To reduce your server load, they should not be updated unnessecarily though. Set your preferred update interval. Lists are updated by running cron.'),
    '#options' => $update_intervals,
    '#default_value' => variable_get('armory_serverlists_maxage', 604800),
  );

  $guildlist = armory_admin_list_guilds();
  $form['guild_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Registered guilds'),
    '#collapsible' => TRUE,
  );

  $form['guild_settings']['existing_guilds'] = array(
    '#type' => 'item',
    '#value' => $guildlist[0],
    '#description' => t('New guilds are added by <a href="@create_guild" title="Go to the create new guild page">creating guild nodes</a>.', array('@create_guild' => '/node/add/guild')),
  );

  $form['servers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Existing servers'),
  );

  $serverlist = armory_serverlist(); 
  $us_servers = (count($serverlist['us']) > 0) ? theme('item_list', $serverlist['us'], $title = NULL, $type = 'ul') : '<p>'. t('No US servers loaded.') .'</p>';
  $eu_servers = (count($serverlist['eu']) > 0) ? theme('item_list', $serverlist['eu'], $title = NULL, $type = 'ul') : '<p>'. t('No EU servers loaded.') .'</p>';

  $us_collapsed = (count($serverlist['us']) > 0) ? TRUE : FALSE;
  $eu_collapsed = (count($serverlist['eu']) > 0) ? TRUE : FALSE;

  $form['servers']['us'] = array(
    '#type' => 'fieldset',
    '#title' => t('US Servers'),
    '#collapsible' => TRUE,
    '#collapsed' => $us_collapsed,
  );

  $form['servers']['us']['us_servers'] = array(
    '#value' => $us_servers,
  );

  $form['servers']['eu'] = array(
    '#type' => 'fieldset',
    '#title' => t('EU Servers'),
    '#collapsible' => TRUE,
    '#collapsed' => $eu_collapsed,
  );

  $form['servers']['eu']['eu_servers'] = array(
    '#value' => $eu_servers,
  );

  $form = system_settings_form($form);
  unset($form['#submit']);
  $form['#submit'][] = 'armory_settings_submit';
  return $form;

}

function armory_settings_submit($form, &$form_state) {
  // If the user hit the 'Reset to defaults button' we do that then return.
  if ($form_state['clicked_button']['#parents'][0] == 'reset') {
    variable_set('armory_style', 'armory-plain-bright');
    variable_set('armory_intro_text', ARMORY_DEFAULT_INTRO);
    variable_set('armory_serverlists_maxage', 604800);
    variable_set('armory_characters_maxage', 86400);
    variable_set('allowed_guilds_policy', 'all');
    drupal_set_message(t('The configuration options have been reset to their default values.'));
  }
  else {
    $armory_style = $form_state['values']['armory_style'];
    $armory_intro = $form_state['values']['intro_text'];
    $char_maxage = $form_state['values']['characters_maxage'];
    $server_maxage = $form_state['values']['serverlist_maxage'];
    $allowed_guilds_policy = $form_state['values']['allowed_guilds_policy'];
    variable_set('armory_style', $armory_style);
    variable_set('armory_intro_text', $armory_intro);
    variable_set('armory_serverlists_maxage', $server_maxage);
    variable_set('armory_characters_maxage', $char_maxage);
    variable_set('allowed_guilds_policy', $allowed_guilds_policy);
    drupal_set_message('Settings saved.');
  }
}

function armory_get_servers($message = 1) {
  // Regions must be added manually here, and then the logic to process 
  // that region must be written in the function armory_serverlist(), 
  // because Blizzard is using different structures for their XML files 
  // in different regions...
  $remote_files = array(
    'us' => 'http://www.worldofwarcraft.com/realmstatus/status.xml',
    'eu' => 'http://www.wow-europe.com/realmstatus/index.xml',
  );
  $maxage = variable_get('armory_serverlists_maxage', 604800);
  foreach ($remote_files as $region => $uri) {

    // Process the given region and uri.
    $serverlist_dir = file_directory_path() .'/armory/serverlists';
    $local_file = $serverlist_dir .'/'. $region .'.xml';
    $success = armory_get_xml($uri, $serverlist_dir, $local_file, $message, $maxage);
    if ($success === 'not_maxage') {
      if ($message == 1) drupal_set_message(t('Serverlist for @region already up to date. New list was not fetched.', array('@region' => strtoupper($region))));
    }
    elseif ($success == TRUE) {
      if ($message == 1) drupal_set_message(t('Serverlist for @region retrieved.', array('@region' => strtoupper($region))));
    }
    else {
      if ($message == 1) drupal_set_message(t('The list for @region could not be retrieved.', array('@region' => strtoupper($region))), 'warning');
    }
  }
}

function armory_admin_list_guilds() {
  $items = array();
  $headers = array(t('Guildname'), t('Server'), t('Region'));
  $sql = "SELECT * FROM {guilds} ORDER BY region, servername, guildname";
  $pre_result = db_query($sql);
  $total_guilds = db_affected_rows();
  $sql_count = "SELECT COUNT(gid) AS num FROM {guilds}";
  $result = pager_query($sql, 10, 1, $sql_count); 
  while ($row = db_fetch_object($result)) {
    $items[] = array(l($row->guildname, 'node/'. $row->nid), $row->servername, $row->region);
  }
  if (count($items) > 0) {
    $guildstable = theme('table', $headers, $items)
                 . theme('pager', array(), 10, 1)
                 . '<p>'. t('@total_guilds guilds total.', array('@total_guilds' => $total_guilds)) .'</p>';
    return array($guildstable, $total_guilds);
  }
  else {
    return array(t('No guilds in the database yet.'));
  }
}
