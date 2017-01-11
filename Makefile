PROG=		kiosk
CFLAGS!=	pkg-config --cflags gtk+-3.0 webkit2gtk-4.0
LDFLAGS!=	pkg-config --libs gtk+-3.0 webkit2gtk-4.0

.include <bsd.prog.mk>
