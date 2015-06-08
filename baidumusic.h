#ifndef BAIDUMUSIC_H
#define BAIDUMUSIC_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkReply>

#include "cookiejar.h"

class BaiduMusic : public QObject
{
    Q_OBJECT
public:
    explicit BaiduMusic(QObject *parent = 0);
    ~BaiduMusic();

    /**
     * @brief setSearchMode
     * @param mode 搜索模式
     * 		"force"：强制搜索，取消当前搜索
     *      "ignore":如有关键字正在搜索中，则取消这此搜索
     * 		"wait":等待，如果正在搜索中，则等待搜索完毕再执行搜索
     */
    void setSearchMode(const QString& mode);

    /**
     * @brief search 搜索歌曲
     * @param keyword 关键字
     * @param page	页数
     */
    void search(const QString& keyword, int page);

    /**
     * @brief getSuggestion 获取搜索建议
     * @param keyword 百度音乐歌曲id
     */
    void getSuggestion(QString keyword);

    /**
     * @brief getSongInfo 获取歌曲信息
     * @param songId
     */
    void getSongInfo(int songId);

    /**
     * @brief getSongLink 获取歌曲链接，包括下载链接和歌词连接等
     * @param songId
     */
    void getSongLink(int songId);

private:
    QNetworkAccessManager manager;
    QNetworkReply* searchReply;
    QNetworkReply* sugestionReply;
    QNetworkReply* songInfoReply;
    QNetworkReply* songLinkReply;

    QString nextKeywordOfSearch;
    QString nextKeywordOfSug;
    QString nextSongIdOfInfo;
    QString nextSongIdOfLink;

    QString searchMode;

    //保存所有cookie
    CookieJar cookieJar;
private slots:
    void searchReplyFinished();
    void sugestionReplyFinished();
    void songInfoReplyFinished();
    void songLinkReplyFinished();
signals:
    /**
     * @brief searchComplete 搜索完毕
     * @param currentPage 当前页
     * @param pageCount 总页数
     * @param songList 歌曲列表,json数据
     * 	[
     * 		{"songItem":
     * 			{
     * 				"sid":877578,
     * 				"author":"Beyond",
     * 				"sname":"海阔天空",
     * 				"oid":877578,
     * 				"pay_type":"2"
     * 			}
     * 		},
     * 		{"songItem":
     * 			...
     * 		},
     * 		...
     * ]
     */
    void searchComplete(int currentPage,int pageCount,QString songList);

    /**
     * @brief getSuggestionComplete 获取搜索建议完毕
     * @param suggestion 搜索建议json数据
     * {
     *    "data": {
     *           "song": [{
     *               "songid": "877578",
     *               "songname": "\u6d77\u9614\u5929\u7a7a",
     *               "encrypted_songid": "",
     *               "has_mv": "1",
     *               "yyr_artist": "0",
     *               "artistname": "Beyond"
     *           },
     *           ...
     *          ],
     *           "artist": [{
     *               "artistid": "2345733",
     *               "artistname": "\u6d77\u9614\u5929\u7a7a",
     *               "artistpic": "http:\/\/a.hiphotos.baidu.com\/ting\/pic\/item\/6d81800a19d8bc3eb42695cc808ba61ea8d3458d.jpg",
     *               "yyr_artist": "0"
     *           },
     *           ...
     *          ],
     *           "album": [{
     *               "albumid": "197864",
     *               "albumname": "\u6d77\u9614\u5929\u7a7a",
     *               "artistname": "Beyond",
     *               "artistpic": "http:\/\/a.hiphotos.baidu.com\/ting\/pic\/item\/6c224f4a20a4462314dd8c409a22720e0cf3d7f8.jpg"
     *           },
     *           ...
     *           ]
     *       },
     *       "Pro": ["artist", "song", "album"]
     *   }
     *
     */
    void getSuggestionComplete(QString suggestion);

    /**
     * @brief getSongLinkComplete 获取歌曲连接完毕
     * @param songLink
     */
    void getSongLinkComplete(QString songLink);
public slots:
};

#endif // BAIDUMUSIC_H
