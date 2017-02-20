
#include "QCookieJar.h"

QCookieJar::QCookieJar (QString path, QObject *parent) : QNetworkCookieJar(parent)  //on preds en argument le nom du fichier ou l'on doit sauver/charger les cookies
{
	file=path; //on stocke le nom de ce fichier

	QFile cookieFile(this->file);
	if(!cookieFile.open(QIODevice::ReadWrite | QIODevice::Text))
	{
	    qWarning() << "Failed to open" << cookieFile.fileName() << "for write:" << cookieFile.errorString();

	}
	QFileInfo fileInfo(cookieFile);
	QString filepath = fileInfo.filePath();
	QString absulotpath = fileInfo.absoluteFilePath();
	bool sss = fileInfo.isHidden();
	bool b = cookieFile.exists();
	
	
	if (cookieFile.exists() /*&& cookieFile.open(QIODevice::ReadWrite | QIODevice::Text) */)  //si on peut l'ouvrir...
	{
		QList<QNetworkCookie> list;  //on crée une liste vide de cookies
		QByteArray line; //on crée une ligne vide ( ça serviera de mémoire-tampon)
		while(!(line = cookieFile.readLine()).isNull()) //tant qu'on a pas tout lu dans notre fichier...
		{
			list.append(QNetworkCookie::parseCookies(line)); //on parse la ligne en cours pour en faire une cookie qu'on ajoute à notre liste
		}
		setAllCookies(list); //et on charge notre liste <img src="http://s1.wp.com/wp-includes/images/smilies/icon_wink.gif?m=1268956738g" alt=";-)" class="wp-smiley">
	}
	else  //si on ne paut pas ouvrir le fichier...
	{
		qWarning() << "Imposible d'ouvrir "<< this->file << " pour y lire les cookies !"; //...on le dit !
	}

}

QCookieJar::~QCookieJar () //destructeur; sauvegarde les cookies
{
	QList <QNetworkCookie> cookieList;  //on crée une liste de cookies...
	cookieList = allCookies(); //...et on la remplit de toutes nos cookies

	QFile file(this->file); //on n'ouvre notre fichier, dont le nom est dans la variable "file"

	if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) //si on ne peut pas écrire dedans...
	{
		qWarning() << "Impossible d'ouvrir "<< this->file << " pour y stocker les cookies !";  //on le dit !
		return;
	}

	QTextStream out(&file); //sinon, on crée un flux à partir de notre fichier...

	for(int i = 0 ; i < cookieList.size() ; i++) //... et pour chaque cookie qu'on possède...
	{
		QByteArray line =  cookieList.at(i).toRawForm(QNetworkCookie::Full); //...on récupère les données brutes de la cookie...
		QString stringline(line);
		qWarning() << stringline;
		
		out << line << "\n"; //...et on les mets dans le fichier !
		/* NB: n'e pas oublier le \n pour sauter une ligne entre les cookies: sinon ça marche pas ! */
	}

	file.close(); //on ferme le fichier
}

QList<QNetworkCookie>
QCookieJar::cookiesForUrl ( const QUrl & url ) const //est utilisé par le QNetworkManager
{
	return QNetworkCookieJar::cookiesForUrl(url); //on ne touche pas
}

bool
QCookieJar::setCookiesFromUrl ( const QList<QNetworkCookie> & cookieList, const QUrl & url ) //est utilisé par le QNetworkManager
{
	 return QNetworkCookieJar::setCookiesFromUrl(cookieList, url); //on ne touche pas
	 // Avoid silly compiler warning about unused parameter
   /* QUrl u = url;

    QList<QNetworkCookie> cookies = allCookies();
    foreach(QNetworkCookie cookie, cookieList) {
        cookies += cookie;
    }
    setAllCookies(cookies);
    return true;*/
}

