nlsdir      = $(NLSDIR)

CATALOGS = @MOFILES@

CLEANFILES = $(CATALOGS) WindowMaker.pot

# Please keep this sorted in alphabetic order!
EXTRA_DIST = be.po bg.po bs.po ca.po cs.po da.po de.po el.po es.po et.po \
	fi.po fr.po gl.po hr.po hu.po hy.po it.po ja.po ko.po ms.po nl.po \
	no.po pl.po pt.po ro.po ru.po sk.po sv.po tr.po zh_CN.po zh_TW.po

POTFILES  = \
	$(top_srcdir)/src/appicon.c \
	$(top_srcdir)/src/defaults.c \
	$(top_srcdir)/src/dialog.c \
	$(top_srcdir)/src/dock.c \
	$(top_srcdir)/src/dockedapp.c \
	$(top_srcdir)/src/event.c \
	$(top_srcdir)/src/framewin.c \
	$(top_srcdir)/src/icon.c \
	$(top_srcdir)/src/main.c \
	$(top_srcdir)/src/menu.c \
	$(top_srcdir)/src/misc.c \
	$(top_srcdir)/src/monitor.c \
	$(top_srcdir)/src/resources.c \
	$(top_srcdir)/src/rootmenu.c \
	$(top_srcdir)/src/screen.c \
	$(top_srcdir)/src/session.c \
	$(top_srcdir)/src/stacking.c \
	$(top_srcdir)/src/startup.c \
	$(top_srcdir)/src/switchmenu.c \
	$(top_srcdir)/src/texture.c \
	$(top_srcdir)/src/wdefaults.c \
	$(top_srcdir)/src/window.c \
	$(top_srcdir)/src/winmenu.c \
	$(top_srcdir)/src/winspector.c \
	$(top_srcdir)/src/workspace.c

SUFFIXES = .po .mo

.po.mo: 
	msgfmt -c -o $@ $<


all-local: $(CATALOGS)

WindowMaker.pot: $(POTFILES)
	xgettext --default-domain=WindowMaker \
	--add-comments --keyword=_ --keyword=N_ $(POTFILES)
	if cmp -s WindowMaker.po WindowMaker.pot; then \
	    rm -f WindowMaker.po; \
	else \
	    mv -f WindowMaker.po WindowMaker.pot; \
	fi

install-data-local:  $(CATALOGS)
	$(mkinstalldirs) $(DESTDIR)$(nlsdir)
	chmod 755 $(DESTDIR)$(nlsdir) 
	for n in $(CATALOGS) __DuMmY ; do \
		if test "$$n" -a "$$n" != "__DuMmY" ; then \
			l=`basename $$n .mo`; \
			$(mkinstalldirs) $(DESTDIR)$(nlsdir)/$$l/LC_MESSAGES; \
			chmod 755 $(DESTDIR)$(nlsdir)/$$l; \
			chmod 755 $(DESTDIR)$(nlsdir)/$$l/LC_MESSAGES; \
			$(INSTALL_DATA) -m 644 $$n $(DESTDIR)$(nlsdir)/$$l/LC_MESSAGES/WindowMaker.mo; \
		fi; \
	done
