#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

typedef struct {
	GtkWidget *tabLabel;
	GtkWidget *closeTabButton;
	GtkWidget *closeTabButtonImage;
	GtkWidget *isAudioPlayingSymbol;
	GtkWidget *favicon;
	GtkWidget *trBrowserTabLabelContainer;
} TRBrowserTabLabel;

typedef struct {
	WebKitWebView *viewport;
	TRBrowserTabLabel tabLabel;
	WebKitWebContext *tabContext;	
	WebKitWebsiteDataManager *tabWebsiteDataManager;
	WebKitCookieManager *tabCookieManager;
} TRBrowserTab;

TRBrowserTab TRBrowser_TRBrowserTab_new();
TRBrowserTab getCurrentTab(GtkNotebook *tabBar);
TRBrowserTab getNthTab(gint tabIndex, GtkNotebook *tabBar);
void refreshTabLabel(guint tabIndex, GtkNotebook *tabBar, gboolean forFavicon);