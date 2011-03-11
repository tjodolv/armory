Description
------

This module creates a node type to facilitate the collection of and displaying World of Warcraft characters and guilds on your Drupal site. The character information is retrieved from Blizzard's wowarmory.com. The module in itself does nothing except provide a few basic functions and resouces that the included modules characters.module and guilds.module use to create the actual user experience.

Recommended additional modules are:
- jQuery UI (http://drupal.org/project/jquery_ui)
  Simply install this module, and the armory overview page and the character sheets will be tabbed.
- Content Profile (http://drupal.org/project/content_profile)
  Install this module, remove the default Profile node type it supplies, and enable Armory Profile as the Content Profile node type.
  Go to admin/content/node-type/armory-profile and check the box for "Use this content type as a content profile for users".

A template file and two stylesheets plus some icons are included. The template can be overridden by your theme, but be aware that if you are using jquery_ui (as recommended), the id #armory-overview-tabs used in armory.js and armory-overview.tpl.php and the class .characters-character-tabs used in characters.js and theme_characters_characters() should remain intact, with the same html-structure, for the tabbed overview and character sheet to function properly.


Limitations
-----------
- If a character moves to a new server OR changes name, there is no way to verify this. We could base it on the XML-file from Blizzard, but this would also mean that if the Armory went offline, all characters would be considered to have moved AND/OR changed name. Thus, if a person moves his/her character to a new server or changes name, they must update the character profile manually by deleting the existing character info and then adding it again with the new server/name.


Author
------

Fredrik Kilander (tjodolv, http://drupal.org/user/196733/contact)


Resources
---------
- Parts of the code adapted from a tutorial by Stella Power (http://www.stellapower.net/content/ajax-ifying-drupal-node-forms)
- Parts of the code adapted from the Zen theme by John Albin (http://drupal.org/project/zen)
- Icon adapted from the KDE Crystal Clear Project by Everaldo (http://www.everaldo.com/crystal/)


Legal
-----
World of Warcraft® and Blizzard Entertainment® are all trademarks or registered trademarks of Blizzard Entertainment in the United States and/or other countries. These terms and all related materials, logos, and images are copyright © Blizzard Entertainment. This software is in no way associated with or endorsed by Blizzard Entertainment®.

The module (software) in itself and the contained image icons are all released under the GNU GPL v2.