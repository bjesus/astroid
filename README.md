# astroid mua

  A graphical threads-with-tags mail user agent based on [sup] and [notmuch].
  Written in C++ using GTK+, [WebKit] and [gmime].

## design and user interface goals
* operated by keyboard only - but accept mouse clicks
* very lightweight.
* base interface on sup, but allow buffers to be dragged out
  or separated as windows so that multiple views/buffers can be
  seen at one time.
* allow several simultaneous instances.
* display html mail and some attachments inline - steal from
  thunderbird or geary or something.
* render markdown (and friends) as well as syntax highlighting
* built-in crypto (gpg,..) support
* Support: Platforms supported by notmuch and other libraries, specifically:
  Linux, *BSD, Mac, Windows..

## considerations
* Never use deprecated libraries - use as few libraries as possible
* Never rewrite something it exists an active library for
* All database operations / mail handling should be done by notmuch or other
  tools.

## acknowledgements

  The main inspiration for astroid is the [sup] mail user agent. [sup]
  provided inspiration for [notmuch] which separates the mail index from the
  user interface. astroid is using [notmuch] as a backend.

  Some parts of the user interface and layout have been copied or inspired
  by the [Geary] mail client.

## licence

  GNU GPL V3 or later.


[sup]: http://supmua.org
[notmuch]: http://notmuchmail.org/
[Geary]: http://www.yorba.org/projects/geary/
[gmime]: http://spruce.sourceforge.net/gmime/
[webkit]: http://webkitgtk.org/

