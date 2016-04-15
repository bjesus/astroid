# include <string>

# include <gtkmm/socket.h>

# include "plugin.hh"
# include "modes/edit_message.hh"
# include "log.hh"

using std::endl;

namespace Astroid {
  Plugin::Plugin (EditMessage * _em, ustring _server) : server_name (_server) {
    em = _em;

    log << debug << "em: editor server name: " << server_name << endl;

    /* gvim settings */
    editor_cmd  = em->editor_config.get <std::string>("gvim.cmd");
    editor_args = em->editor_config.get <std::string>("gvim.args");

    /* gtk::socket:
     * http://stackoverflow.com/questions/13359699/pyside-embed-vim
     * https://developer.gnome.org/gtkmm-tutorial/stable/sec-plugs-sockets-example.html.en
     * https://mail.gnome.org/archives/gtk-list/2011-January/msg00041.html
     */
    editor_socket = Gtk::manage(new Gtk::Socket ());
    editor_socket->set_can_focus (true);
    editor_socket->signal_plug_added ().connect (
        sigc::mem_fun(*this, &Plugin::plug_added) );
    editor_socket->signal_plug_removed ().connect (
        sigc::mem_fun(*this, &Plugin::plug_removed) );

    editor_socket->signal_realize ().connect (
        sigc::mem_fun(*this, &Plugin::socket_realized) );

    add (*editor_socket);
  }

  Plugin::~Plugin () {

  }

  bool Plugin::ready () {
    return editor_ready;
  }

  bool Plugin::started () {
    return editor_started;
  }

  void Plugin::start () {
    if (socket_ready) {
      ustring cmd = ustring::compose ("%1 -geom 10x10 --servername %3 --socketid %4 %2 %5",
          editor_cmd, editor_args, server_name, editor_socket->get_id (),
          em->tmpfile_path.c_str());
      log << info << "em: starting gvim: " << cmd << endl;
      Glib::spawn_command_line_async (cmd.c_str());
      vim_started = true;
    } else {
      start_editor_when_ready = true; // TODO: not thread-safe
      log << debug << "em: gvim, waiting for socket.." << endl;
    }

  }

  void Plugin::stop () {

  }

  void Plugin::socket_realized ()
  {
    log << debug << "em: socket realized." << endl;
    socket_ready = true;

    if (start_editor_when_ready) {
      em->editor_toggle (true);
      start_editor_when_ready = false;
    }
  }

  void Plugin::plug_added () {
    log << debug << "em: gvim connected" << endl;

    vim_ready = true;
  }

  bool Plugin::plug_removed () {
    log << debug << "em: gvim disconnected" << endl;
    vim_ready   = false;
    vim_started = false;
    em->editor_toggle (false);

    return true;
  }

}

