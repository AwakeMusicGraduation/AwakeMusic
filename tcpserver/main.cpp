#include "mainwindow.h"
#include "server.h"
#include "sqltable.h"
#include "music.h"
#include "musicbroker.h"
#include <QApplication>
//1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Server *server = new Server;
    //server->show();
    Sqltable *sqltable = new Sqltable();
//    sqltable->query();
    //sqltable->insertParmeterUser("123","123");
    //sqltable->insertParmeterUser("123456","123456");
    //sqltable->login("123456","123456");
//    sqltable->login("123","123");
    //sqltable->createMusicList("favor");
//    sqltable->insertMusicList("favor","初学者","初学者","薛之谦");
//    sqltable->deleteMusicList("favor","初学者","初学者","薛之谦");




//     sqltable->insertParmeter(1,"初学者","薛之谦","/root/薛之谦/初学者/chuxuezhe.lrc","/root/薛之谦/chuxuezhe","初学者");
//        sqltable->insertParmeter(2,"刚刚好","薛之谦","/root/薛之谦/初学者/gangganghao.lrc","/root/薛之谦/chuxuezhe","初学者");
//        sqltable->insertParmeter(3,"花儿和少年","薛之谦","/root/薛之谦/初学者/huaerheshaonian.lrc","/root/薛之谦/chuxuezhe","初学者");
//        sqltable->insertParmeter(4,"我好像在哪见过你","薛之谦","/root/薛之谦/初学者/wohaxiangzainaerjianguoni.lrc","/root/薛之谦/chuxuezhe","初学者");
//        sqltable->insertParmeter(5,"Stay Here","薛之谦","/root/薛之谦/初学者/Stay Here.lrc","/root/薛之谦/chuxuezhe","初学者");

//        sqltable->insertParmeter(5,"背过手","薛之谦","/root/薛之谦/渡/beiguishou.lrc","/root/薛之谦/du","渡");
//        sqltable->insertParmeter(6,"别","薛之谦","/root/薛之谦/渡/bie.lrc","/root/薛之谦/du","渡");
//        sqltable->insertParmeter(7,"动物世界","薛之谦","/root/薛之谦/渡/dongwushijie.lrc","/root/薛之谦/du","渡");
//        sqltable->insertParmeter(8,"渡","薛之谦","/root/薛之谦/渡/du.lrc","/root/薛之谦/du","渡");
//        sqltable->insertParmeter(9,"高尚","薛之谦","/root/薛之谦/渡/gaoshang.lrc","/root/薛之谦/du","渡");
//        sqltable->insertParmeter(10,"火星人来过","薛之谦","/root/薛之谦/渡/huoxingrenlaiguo.lrc","/root/薛之谦/du","渡");
//        sqltable->insertParmeter(11,"骆驼","薛之谦","/root/薛之谦/渡/luotuo.lrc","/root/薛之谦/du","渡");
//        sqltable->insertParmeter(12,"我害怕","薛之谦","/root/薛之谦/渡/wohaipa.lrc","/root/薛之谦/du","渡");
//        sqltable->insertParmeter(13,"像风一样","薛之谦","/root/薛之谦/渡/xiangfengyiyang.lrc","/root/薛之谦/du","渡");
//        sqltable->insertParmeter(14,"暧昧","薛之谦","/root/薛之谦/渡/aimei.lrc","/root/薛之谦/du","渡");

//        sqltable->insertParmeter(15,"怪咖","薛之谦","/root/薛之谦/怪咖/guaika.lrc","/root/薛之谦/guaika","怪咖");

//        sqltable->insertParmeter(16,"狐狸","薛之谦","/root/薛之谦/怪咖/huli.lrc","/root/薛之谦/guaika","怪咖");
//        sqltable->insertParmeter(17,"摩天大楼","薛之谦","/root/薛之谦/怪咖/motiandalou.lrc","/root/薛之谦/guaika","怪咖");
//        sqltable->insertParmeter(18,"那是你离开了北京的生活","薛之谦","/root/薛之谦/怪咖/nashinilikailebeijingdeshenghuo","/root/薛之谦/guaika","怪咖");
//        sqltable->insertParmeter(19,"肆无忌惮","薛之谦","/root/薛之谦/怪咖/siwujidna.lrc","/root/薛之谦/guaika","怪咖");
//        sqltable->insertParmeter(20,"天份","薛之谦","/root/薛之谦/怪咖/tianfen.lrc","/root/薛之谦/guaika","怪咖");
//        sqltable->insertParmeter(21,"哑巴","薛之谦","/root/薛之谦/怪咖/yaba.lrc","/root/薛之谦/guaika","怪咖");
//        sqltable->insertParmeter(22,"最好","薛之谦","/root/薛之谦/怪咖/zuihao.lrc","/root/薛之谦/guaika","怪咖");

//        sqltable->insertParmeter(23,"伏笔","薛之谦","/root/薛之谦/几个薛之谦/fubi.lrc","/root/薛之谦/jigexuezhiqian","几个薛之谦");
//        sqltable->insertParmeter(24,"几个你","薛之谦","/root/薛之谦/几个薛之谦/jigeni.lrc","/root/薛之谦/jigexuezhiqian","几个薛之谦");
//        sqltable->insertParmeter(25,"为了遇见你","薛之谦","/root/薛之谦/几个薛之谦/weileyujianni.lrc","/root/薛之谦/jigexuezhiqian","几个薛之谦");
//        sqltable->insertParmeter(26,"我知道你都知道","薛之谦","/root/薛之谦/几个薛之谦/wozhidaonidouzhidao.lrc","/root/薛之谦/jigexuezhiqian","几个薛之谦");
//        sqltable->insertParmeter(27,"我终于成了别人的女人","薛之谦","/root/薛之谦/几个薛之谦/wozhongyuchengweilebierendenvren.lrc","/root/薛之谦/jigexuezhiqian","几个薛之谦");

//        sqltable->insertParmeter(28,"绅士","薛之谦","/root/薛之谦/绅士/shenshi.lrc","/root/薛之谦/shenshi","绅士");
//        sqltable->insertParmeter(29,"下雨了","薛之谦","/root/薛之谦/绅士/xiayule.lrc","/root/薛之谦/shenshi","绅士");
//        sqltable->insertParmeter(30,"演员","薛之谦","/root/薛之谦/绅士/yanyuan.lrc","/root/薛之谦/shenshi","绅士");

//        sqltable->insertParmeter(31,"传说","薛之谦","/root/薛之谦/深深爱过你/传说-薛之谦.lrc","/root/薛之谦/shenshenaiguoni","深深爱过你");
//        sqltable->insertParmeter(32,"梦开始的原点","薛之谦","/root/薛之谦/深深爱过你/mengkaishideyuandian.lrc","/root/薛之谦/shenshenaiguoni","深深爱过你");

//        sqltable->insertParmeter(33,"爱我的人 谢谢你","薛之谦","/root/薛之谦/未完成的歌/aiwoderenxiexieni.lrc","/root/薛之谦/weiwanchengdege","未完成的歌");
//        sqltable->insertParmeter(34,"未完成的歌","薛之谦","/root/薛之谦/未完成的歌/weiwanchengdege.lrc","/root/薛之谦/weiwanchengdege","未完成的歌");

//        //sqltable->insertParmeter(35,"爱我的人 谢谢你","薛之谦","lyric","/root/薛之谦/womenaiguojiuhao","我们爱过就好");

//        sqltable->insertParmeter(35,"一半","薛之谦","/root/薛之谦/一半/yiban.lrc","/root/薛之谦/yiban","一半");
//        sqltable->insertParmeter(36,"小孩","薛之谦","/root/薛之谦/一半/小孩-薛之谦.lrc","/root/薛之谦/yiban","一半");

//        sqltable->insertParmeter(37,"潮流季","薛之谦","/root/薛之谦/意外/chaoliuji.lrc","/root/薛之谦/yiwai","意外");
//        sqltable->insertParmeter(38,"丑八怪","薛之谦","/root/薛之谦/意外/choubaguai.lrc","/root/薛之谦/yiwai","意外");
//        sqltable->insertParmeter(39,"等我回家","薛之谦","/root/薛之谦/意外/dengwohuijia.lrc","/root/薛之谦/yiwai","意外");
//        sqltable->insertParmeter(40,"方圆几里","薛之谦","/root/薛之谦/意外/fangyuanjili.lrc","/root/薛之谦/yiwai","意外");
//        sqltable->insertParmeter(41,"你还要我怎样","薛之谦","/root/薛之谦/意外/nihaiyaowozenyang.lrc","/root/薛之谦/yiwai","意外");
//        sqltable->insertParmeter(42,"其实","薛之谦","/root/薛之谦/意外/qishi.lrc","/root/薛之谦/yiwai","意外");
//        sqltable->insertParmeter(43,"我想起你了","薛之谦","/root/薛之谦/意外/woxiangqinile.lrc","/root/薛之谦/yiwai","意外");
//        sqltable->insertParmeter(44,"意外","薛之谦","/root/薛之谦/意外/yiwai.lrc","/root/薛之谦/yiwai","意外");
//        sqltable->insertParmeter(45,"有没有","薛之谦","/root/薛之谦/意外/youmeiyou.lrc","/root/薛之谦/yiwai","意外");

//      sqltable->insertParmeter(46,"当一切结束时","岛屿心情","/root/songs/岛屿心情/岛屿心情/dangyiqiejieshushi.lrc","/root/album/daoyuxinqing","岛屿心情");
//         sqltable->insertParmeter(47,"玩具","岛屿心情","/root/songs/岛屿心情/岛屿心情/wanju.lrc","/root/album/daoyuxinqing2","纷纭");
//         sqltable->insertParmeter(48,"爱你就像爱生命","房东的猫","/root/songs/房东的猫/爱你就像爱生命/ainijiuxiangaishengming.lrc","/root/album/fangdongdemao","房东的猫");
//         sqltable->insertParmeter(49,"那片海","韩红","/root/songs/韩红/韩红精选/napianhai.lrc","/root/album/hanhong","韩红精选");
//         sqltable->insertParmeter(50,"冰雨","刘德华","/root/songs/刘德华/你是我的骄傲演唱会/bingyu.lrc","/root/album/liudehua","你是我的骄傲演唱会");
//         sqltable->insertParmeter(51,"秋酿","房东的猫","/root/songs/房东的猫/我们正青春/qiuniang.lrc","/root/album/fangdongdemao","我们正青春");
//         sqltable->insertParmeter(52,"公路之歌","痛仰乐队","/root/songs/痛仰乐队/不要停止我的音乐/gongluzhige.lrc","/root/album/tongyang","不要停止我的音乐");
//         sqltable->insertParmeter(53,"再见杰克","痛仰乐队","/root/songs/痛仰乐队/不要停止我的音乐/zaijianjieke.lrc","/root/album/tongyang","不要停止我的音乐");
//         sqltable->insertParmeter(54,"恶作剧","王蓝茵","/root/songs/王蓝茵/恶作剧之吻/ezuoju.lrc","/root/album/wanglanyin","恶作剧之吻");
//         sqltable->insertParmeter(55,"暗里着迷","刘德华","/root/songs/刘德华/WouderfulWorld/anlizhaomi.lrc","/root/album/liudehua2","WonderfulWorld");


//       sqltable->insertParmeterSinger(0,"薛之谦","男歌手");
//       sqltable->insertParmeterSinger(1,"岛屿心情","乐队");
//      sqltable->insertParmeterSinger(2,"房东的猫","乐队");
//      sqltable->insertParmeterSinger(3,"韩红","女歌手");
//      sqltable->insertParmeterSinger(4,"刘德华","男歌手");
//      sqltable->insertParmeterSinger(5,"痛仰乐队","乐队");
//      sqltable->insertParmeterSinger(6,"王蓝茵","女歌手");


//     sqltable->insertParmeterAlbum(0,"几个薛之谦","2012-08-15","薛之谦");
//     sqltable->insertParmeterAlbum(1,"初学者","2016-07-18","薛之谦");
//     sqltable->insertParmeterAlbum(2,"怪咖","2018-12-31","薛之谦");
//     sqltable->insertParmeterAlbum(3,"渡","2017-11-28","薛之谦");
//     sqltable->insertParmeterAlbum(4,"深深爱过你","2008-11-24","薛之谦");
//     sqltable->insertParmeterAlbum(5,"未完成的歌","2012-12-01","薛之谦");
//     sqltable->insertParmeterAlbum(6,"绅士","2015-06-05","薛之谦");
//     sqltable->insertParmeterAlbum(7,"我们爱过就好","2010-10-31","薛之谦");
//     sqltable->insertParmeterAlbum(8,"一半","2015-10-17","薛之谦");
//     sqltable->insertParmeterAlbum(9,"意外","2013-11-11","薛之谦");
//     sqltable->insertParmeterAlbum(10,"岛屿心情","2011-09-25","岛屿心情");
//  sqltable->insertParmeterAlbum(11,"纷纭","2015-08-12","岛屿心情");
//  sqltable->insertParmeterAlbum(12,"韩红精选","2015-05-15","韩红");
//  sqltable->insertParmeterAlbum(13,"你是我的骄傲演唱会","2002-12-01","刘德华");
//  sqltable->insertParmeterAlbum(14,"我们正青春","2016-01-23","房东的猫");
//  sqltable->insertParmeterAlbum(15,"不要停止我的音乐","2008-09-30","痛仰乐队");
//  sqltable->insertParmeterAlbum(16,"恶作剧之吻","2005-10-21","王蓝茵");
//  sqltable->insertParmeterAlbum(17,"WonderfulWorld","2008-02-01","刘德华");


//     sqltable->insertParmeterTransform("有没有","youmeiyou");
//     sqltable->insertParmeterTransform("意外","yiwai");
//     sqltable->insertParmeterTransform("我想起你了","woxiangqileni");
//     sqltable->insertParmeterTransform("其实","qishi");
//     sqltable->insertParmeterTransform("你还要我怎样","nihaiyaowozenyang");
//     sqltable->insertParmeterTransform("方圆几里","fangyuanjili");
//     sqltable->insertParmeterTransform("等我回家","dengwohuijia");
//     sqltable->insertParmeterTransform("丑八怪","choubaguai");
//     sqltable->insertParmeterTransform("潮流季","chaoliuji");
//     sqltable->insertParmeterTransform("一半","yiban");
//     sqltable->insertParmeterTransform("小孩","xiaohai");
//     sqltable->insertParmeterTransform("我们爱过就好","womenaiguojiuhao");
//     sqltable->insertParmeterTransform("未完成的歌","weiwanchengdege");
//     sqltable->insertParmeterTransform("爱我的人","aiwoderen");
//     sqltable->insertParmeterTransform("梦开始的原点","mengkaishideyuandian");
//     sqltable->insertParmeterTransform("传说","chuanshuo");
//     sqltable->insertParmeterTransform("演员","yanyuan");
//     sqltable->insertParmeterTransform("下雨了","xiayule");
//     sqltable->insertParmeterTransform("绅士","shenshi");
//     sqltable->insertParmeterTransform("我终于成了别人的女人","wozhongyuchenglebierendenvren");
//     sqltable->insertParmeterTransform("我知道你都知道","wozhidaonidouzhidao");
//     sqltable->insertParmeterTransform("为了遇见你","weileyujianni");
//     sqltable->insertParmeterTransform("几个你","jigeni");
//     sqltable->insertParmeterTransform("伏笔","fubi");
//     sqltable->insertParmeterTransform("最好","zuihao");
//     sqltable->insertParmeterTransform("哑巴","yaba");
//     sqltable->insertParmeterTransform("天份","tianfen");
//     sqltable->insertParmeterTransform("肆无忌惮","siwujidan");
//     sqltable->insertParmeterTransform("那是你离开了北京的生活","nashinilikailebeijingdeshenghuo");
//     sqltable->insertParmeterTransform("摩天大楼","motiandalou");
//     sqltable->insertParmeterTransform("狐狸","huli");
//     sqltable->insertParmeterTransform("怪咖","guaika");
//     sqltable->insertParmeterTransform("暧昧","aimei");
//     sqltable->insertParmeterTransform("像风一样","xiangfengyiyang");
//     sqltable->insertParmeterTransform("我害怕","wohaipa");
//     sqltable->insertParmeterTransform("骆驼","luotuo");
//     sqltable->insertParmeterTransform("火星人来过","huoxingrenlaiguo");
//     sqltable->insertParmeterTransform("高尚","gaoshang");
//     sqltable->insertParmeterTransform("渡","du");
//     sqltable->insertParmeterTransform("动物世界","dongwushijie");
//     sqltable->insertParmeterTransform("别","bie");
//     sqltable->insertParmeterTransform("背过手","beiguoshou");
//     sqltable->insertParmeterTransform("Stay Here","stayhere");
//     sqltable->insertParmeterTransform("我好想在哪儿见过你","wohaoxiangzainaerjianguoni");
//     sqltable->insertParmeterTransform("花儿和少年","huaerheshaonian");
//     sqltable->insertParmeterTransform("刚刚好","gangganghao");
//     sqltable->insertParmeterTransform("初学者","chuxuezhe");
//      sqltable->insertParmeterTransform("当一切结束时","dangyiiejieshushi");
//      sqltable->insertParmeterTransform("玩具","wanju");
//      sqltable->insertParmeterTransform("爱你就像爱生命","ainijiuxiangaishengming");
//      sqltable->insertParmeterTransform("那片海","napianhai");
//      sqltable->insertParmeterTransform("冰雨","bingyu");
//      sqltable->insertParmeterTransform("秋酿","qiuniang");
//      sqltable->insertParmeterTransform("公路之歌","gongluzhige");
//      sqltable->insertParmeterTransform("再见杰克","zaijianjieke");
//      sqltable->insertParmeterTransform("恶作剧","ezuoju");
//      sqltable->insertParmeterTransform("暗里着迷","anlizhaomi");

    MainWindow *w=new MainWindow;
    w->show();
    return a.exec();
}
