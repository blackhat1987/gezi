#ifndef GBK_COMPLEX_SIMPLIFY_TABLE_H_
#define GBK_COMPLEX_SIMPLIFY_TABLE_H_

namespace ch_convert 
{

static const char * const ComplexFonts[] = {
"丟","並","亂","亙","亞","伕","佇","佈","佔","併","來","侖","侶","侷","俁","係","俠","倀","倆","倉",
"個","們","倖","倣","倫","偉","側","偵","偸","偺","偽","傑","傖","傘","備","傚","傢","傭","傯","傳",
"傴","債","傷","傾","僂","僅","僉","僑","僕","僞","僥","僨","僱","價","儀","儂","億","儅","儈","儉",
"儐","儔","儕","儘","償","優","儲","儷","儸","儹","儺","儻","儼","兇","兌","兒","兗","內","兩","冊",
"冪","凃","凍","凜","凟","処","凱","凴","別","刪","剄","則","剋","剗","剛","剝","剮","剴","創","剷",
"劃","劄","劇","劉","劊","劌","劍","劑","劒","勁","動","勗","務","勛","勝","勞","勢","勣","勦","勩",
"勱","勳","勵","勸","勻","匭","匯","匱","匲","匳","匵","區","協","卹","卻","厙","厛","厠","厤","厭",
"厰","厲","厴","參","叢","吳","呂","咼","員","哢","唄","唕","唚","唸","問","啓","啗","啞","啟","啢",
"啣","喒","喚","喦","喪","喫","喬","單","喲","嗆","嗇","嗊","嗎","嗚","嗩","嗶","嘆","嘍","嘔","嘖",
"嘗","嘜","嘩","嘮","嘯","嘰","嘵","嘸","嘽","噁","噅","噓","噝","噠","噥","噦","噯","噲","噴","噸",
"噹","嚀","嚇","嚌","嚐","嚕","嚙","嚥","嚦","嚨","嚮","嚲","嚳","嚴","嚶","嚻","囀","囁","囂","囅",
"囈","囉","囌","囑","囘","囪","囬","囯","圇","國","圍","園","圓","圖","團","坰","垵","垻","埡","埰",
"執","堅","堊","堖","堝","堦","堯","報","場","堿","塊","塋","塏","塒","塗","塚","塢","塤","塲","塵",
"塹","塼","墊","墜","墝","墮","墰","墳","墶","墻","墾","壇","壋","壎","壓","壘","壙","壚","壜","壞",
"壟","壠","壢","壩","壪","壯","壺","壼","壽","夀","夠","夢","夾","奐","奧","奩","奪","奮","妝","姍",
"姦","姪","娛","娬","婁","婦","婬","婭","媧","媮","媯","媼","媽","嫋","嫗","嫵","嫺","嫻","嫿","嬀",
"嬈","嬋","嬌","嬙","嬝","嬡","嬤","嬪","嬭","嬰","嬸","嬾","孃","孌","孫","學","孿","宮","寢","實",
"寧","審","寫","寬","寵","寶","尅","將","專","尋","對","導","尲","尷","屆","屍","屓","屜","屢","層",
"屨","屬","屭","岡","峴","島","峽","崍","崐","崑","崗","崙","崠","崢","崬","崳","嵐","嵗","嶁","嶄",
"嶇","嶔","嶗","嶠","嶢","嶧","嶨","嶮","嶴","嶸","嶺","嶼","嶽","巋","巒","巔","巖","巰","巹","帥",
"師","帳","帶","幀","幃","幗","幘","幟","幣","幫","幬","幱","幹","幾","庫","廁","廂","廄","廈","廎",
"廕","廚","廝","廟","廠","廡","廢","廣","廩","廬","廳","廻","廼","弔","弳","張","強","彆","彈","彊",
"彌","彎","彙","彜","彞","彠","彥","彫","彿","徑","從","徠","復","徬","徴","徹","恆","恥","悅","悵",
"悶","悽","惡","惱","惲","惻","愛","愜","愨","愴","愷","愾","慄","慇","態","慍","慘","慙","慚","慟",
"慣","慤","慪","慫","慮","慳","慴","慶","慼","慾","憂","憊","憐","憑","憒","憖","憚","憤","憫","憮",
"憲","憶","懇","應","懌","懍","懕","懞","懟","懣","懨","懲","懶","懷","懸","懺","懼","懽","懾","戀",
"戇","戔","戧","戩","戯","戰","戲","戶","扡","挾","捨","捫","捲","掃","掄","掗","掙","掛","採","揀",
"揚","換","揮","揹","搆","搇","損","搖","搗","搶","搾","摑","摜","摟","摣","摯","摳","摶","摻","撈",
"撏","撐","撓","撚","撟","撣","撥","撫","撲","撳","撻","撾","撿","擁","擄","擇","擊","擋","擔","擕",
"據","擠","擡","擣","擧","擬","擯","擰","擱","擲","擴","擷","擺","擻","擼","擾","攄","攆","攏","攔",
"攖","攙","攛","攜","攝","攢","攣","攤","攩","攪","攬","攷","敍","敗","敘","敭","敵","數","敺","斂",
"斃","斕","斬","斷","旂","昇","時","晉","晝","暈","暉","暘","暢","暫","暱","曄","曆","曇","曉","曏",
"曖","曠","曡","曨","曬","書","會","朧","東","枴","柵","柺","桿","梔","梘","條","梟","梱","棄","棖",
"棗","棟","棧","棬","棲","棶","椏","楊","楓","楨","業","極","榦","榪","榮","榿","槃","構","槍","槓",
"槧","槨","槳","槼","樁","樂","樅","樑","樓","標","樞","樣","樷","樸","樹","樺","橈","橋","機","橢",
"橫","橰","檁","檉","檔","檜","檟","檢","檣","檮","檯","檳","檸","檻","檾","櫂","櫃","櫓","櫚","櫛",
"櫝","櫞","櫟","櫥","櫧","櫨","櫪","櫫","櫬","櫳","櫸","櫺","櫻","欄","權","欏","欑","欒","欖","欞",
"欽","歎","歐","歗","歛","歟","歡","歲","歷","歸","歿","殘","殞","殤","殫","殮","殯","殲","殺","殼",
"毀","毆","毉","毧","毬","毿","氂","氈","氊","氌","氣","氫","氬","氳","氹","氾","汎","汙","汚","決",
"沍","沒","沖","況","洩","洶","浹","涇","涖","涼","淒","淚","淥","淨","淩","淪","淵","淶","淺","渙",
"減","渢","渦","測","渾","湊","湞","湣","湧","湯","溈","準","溝","溫","溮","溳","溼","滄","滅","滌",
"滎","滙","滬","滯","滲","滷","滸","滻","滾","滿","漁","漊","漚","漢","漣","漬","漲","漵","漸","漿",
"潁","潑","潔","潙","潛","潟","潤","潯","潰","潷","潿","澀","澁","澂","澆","澇","澗","澠","澤","澦",
"澩","澮","澱","濁","濃","濔","濕","濘","濛","濜","濟","濤","濫","濬","濰","濱","濶","濺","濼","濾",
"瀅","瀆","瀉","瀋","瀏","瀕","瀘","瀝","瀟","瀠","瀦","瀧","瀨","瀰","瀲","瀾","灃","灄","灑","灕",
"灘","灝","灣","灤","灧","灩","災","炤","為","烏","烴","無","煆","煇","煉","煒","煖","煙","煢","煥",
"煩","煬","熒","熗","熱","熲","熾","燁","燄","燈","燉","燐","燒","燙","燜","營","燦","燬","燭","燴",
"燻","燼","燾","燿","爍","爐","爗","爛","爭","爲","爺","爾","牀","牆","牋","牐","牘","牴","牽","犖",
"犛","犢","犧","狀","狹","狽","猙","猶","猻","獁","獃","獄","獅","獎","獨","獪","獫","獮","獰","獲",
"獵","獷","獸","獺","獻","獼","玀","玆","玨","珮","現","琍","琯","琺","琿","瑉","瑋","瑒","瑣","瑤",
"瑩","瑪","瑯","瑲","璉","璡","璣","璦","璫","環","璵","璽","璿","瓊","瓏","瓔","瓚","甌","甎","甕",
"甖","產","産","甦","畝","畢","畫","異","畱","當","疇","疊","痙","痠","痺","瘂","瘉","瘋","瘍","瘓",
"瘞","瘡","瘧","瘮","瘺","瘻","療","癆","癇","癉","癒","癘","癟","癡","癢","癤","癥","癧","癩","癬",
"癭","癮","癰","癱","癲","發","皚","皰","皸","皺","盃","盜","盞","盡","監","盤","盧","盪","眎","眡",
"眥","眾","睏","睜","睞","瞘","瞞","瞼","矇","矓","矚","矯","砲","硃","硜","硤","硨","硯","硶","碩",
"碭","碸","確","碼","磑","磚","磣","磧","磯","磽","礄","礎","礙","礦","礪","礫","礬","礮","礱","祐",
"祕","祿","禍","禎","禕","禦","禪","禮","禰","禱","禿","秈","稅","稈","稜","稟","稭","種","稱","穀",
"穌","積","穎","穠","穡","穢","穨","穩","穫","穭","窩","窪","窮","窯","窰","窶","窺","竄","竅","竇",
"竈","竊","竝","竪","競","筆","筍","筧","箇","箋","箏","箠","節","範","築","篋","篛","篠","篤","篩",
"篳","簀","簍","簑","簞","簡","簣","簫","簷","簹","簽","簾","籃","籌","籐","籙","籜","籟","籠","籢",
"籤","籥","籩","籪","籬","籮","籲","粧","粬","粵","糝","糞","糢","糧","糰","糲","糴","糶","糾","紀",
"紂","約","紅","紆","紇","紈","紉","紋","納","紐","紓","純","紕","紖","紗","紘","紙","級","紛","紜",
"紝","紡","紥","紮","細","紱","紲","紳","紵","紹","紺","紼","紿","絀","終","絃","組","絆","絍","絎",
"絏","結","絕","絛","絝","絞","絡","絢","給","絨","絰","統","絲","絳","絹","綁","綃","綆","綈","綉",
"綌","綏","綑","經","綜","綞","綠","綢","綣","綫","綬","維","綯","綰","綱","網","綳","綴","綵","綸",
"綹","綺","綻","綽","綾","綿","緄","緇","緊","緋","緍","緒","緓","緔","緗","緘","緙","線","緜","緝",
"緞","締","緡","緣","緤","緦","編","緩","緬","緯","緱","緲","練","緶","緹","緻","緼","縂","縈","縉",
"縊","縋","縐","縑","縕","縗","縚","縛","縝","縞","縟","縣","縧","縫","縭","縮","縯","縱","縲","縴",
"縵","縶","縷","縹","總","績","繃","繅","繆","繈","繒","織","繕","繖","繙","繚","繞","繡","繢","繦",
"繩","繪","繫","繭","繮","繯","繰","繳","繹","繼","繽","繾","纇","纈","纊","續","纍","纏","纓","纖",
"纘","纜","缽","罈","罋","罌","罎","罏","罰","罵","罷","罸","羅","羆","羈","羋","羢","羥","羨","義",
"羶","習","翬","翹","翺","翽","耑","耡","耬","耮","聖","聞","聯","聰","聲","聳","聵","聶","職","聹",
"聼","聽","聾","肅","脅","脇","脈","脛","脣","脩","脫","脹","腎","腖","腡","腦","腫","腳","腸","膁",
"膃","膕","膚","膠","膩","膽","膾","膿","臉","臍","臏","臒","臘","臚","臟","臠","臢","臥","臨","臯",
"臺","與","興","舉","舊","舖","舘","艙","艢","艣","艤","艦","艪","艫","艱","艷","艸","芻","苧","茲",
"荊","莊","莖","莢","莧","華","菴","萇","萊","萬","萵","葉","葒","葠","葤","葦","葯","葷","蒐","蒓",
"蒔","蒞","蒼","蓀","蓆","蓋","蓡","蓧","蓮","蓯","蓴","蓽","蔆","蔔","蔞","蔣","蔥","蔦","蔭","蔴",
"蕁","蕆","蕎","蕒","蕓","蕕","蕘","蕢","蕩","蕪","蕭","蕷","薈","薊","薌","薑","薔","薘","薟","薦",
"薩","薺","藍","藎","藝","藥","藪","藶","藹","藺","蘀","蘄","蘆","蘇","蘊","蘋","蘚","蘞","蘢","蘭",
"蘺","蘿","處","虛","虜","號","虧","虯","蛺","蛻","蜆","蝕","蝟","蝦","蝨","蝸","螄","螘","螞","螢",
"螻","螿","蟄","蟈","蟎","蟣","蟬","蟯","蟲","蟶","蟻","蠅","蠆","蠍","蠐","蠑","蠔","蠟","蠣","蠨",
"蠱","蠶","蠻","衆","衊","術","衚","衛","衝","衞","衹","袞","裊","裌","裏","補","裝","裡","製","複",
"褌","褘","褲","褳","褸","褻","襆","襇","襍","襏","襖","襝","襠","襤","襪","襯","襲","襴","覈","見",
"覎","規","覓","覔","視","覘","覜","覡","覥","覦","親","覬","覯","覰","覲","覷","覺","覻","覽","覿",
"觀","觝","觴","觶","觸","訁","訂","訃","計","訊","訌","討","訏","訐","訒","訓","訕","訖","託","記",
"訛","訝","訟","訢","訣","訥","訦","訩","訪","設","許","訴","訶","診","註","証","詁","詆","詎","詐",
"詒","詔","評","詖","詗","詘","詛","詞","詠","詡","詢","詣","試","詩","詫","詬","詭","詮","詰","話",
"該","詳","詵","詼","詾","詿","誄","誅","誆","誇","誌","認","誑","誒","誕","誘","誚","語","誠","誡",
"誣","誤","誥","誦","誨","說","説","誰","課","誶","誹","誼","調","諂","諄","談","諉","請","諍","諏",
"諑","諒","論","諗","諛","諜","諝","諞","諡","諢","諤","諦","諧","諫","諭","諮","諱","諳","諶","諷",
"諸","諺","諼","諾","謀","謁","謂","謄","謅","謊","謎","謐","謔","謖","謗","謙","謚","講","謝","謠",
"謨","謫","謬","謳","謹","謾","譁","譆","證","譌","譎","譏","譖","識","譙","譚","譜","譟","譫","譭",
"譯","議","譴","護","譸","譽","譾","讀","讁","讅","變","讋","讌","讎","讐","讒","讓","讕","讖","讚",
"讛","讜","讞","谿","豈","豎","豐","豔","豬","豶","貍","貓","貝","貞","貟","負","財","貢","貧","貨",
"販","貪","貫","責","貯","貰","貲","貳","貴","貶","買","貸","貺","費","貼","貽","貿","賀","賁","賂",
"賃","賄","賅","資","賈","賉","賊","賍","賑","賒","賓","賔","賕","賙","賚","賛","賜","賞","賠","賡",
"賢","賣","賤","賦","賧","質","賫","賬","賭","賮","賴","賵","賸","賺","賻","購","賽","賾","贄","贅",
"贇","贈","贊","贋","贍","贏","贐","贓","贔","贖","贗","贛","贜","赬","趕","趙","趨","趲","跡","跼",
"踐","踡","踴","蹌","蹕","蹟","蹠","蹣","蹤","蹺","躂","躉","躊","躋","躍","躑","躒","躓","躕","躚",
"躡","躥","躦","躪","躰","軀","軃","車","軋","軌","軍","軑","軒","軔","軛","軟","軤","軫","軲","軸",
"軹","軺","軻","軼","軾","較","輅","輇","輈","載","輊","輒","輓","輔","輕","輛","輜","輝","輞","輟",
"輥","輦","輩","輪","輬","輭","輯","輳","輸","輻","輼","輾","輿","轀","轂","轄","轅","轆","轉","轍",
"轎","轔","轟","轡","轢","轤","辤","辦","辭","辮","辯","農","辳","迆","迴","迺","逕","這","連","週",
"進","遊","運","過","達","違","遙","遜","遝","遞","遠","適","遲","遷","選","遺","遼","邁","還","邇",
"邊","邏","邐","郃","郟","郤","郵","鄆","鄉","鄒","鄔","鄕","鄖","鄘","鄧","鄭","鄰","鄲","鄴","鄶",
"鄺","酈","酧","醃","醖","醜","醞","醫","醬","醱","醻","醼","釀","釁","釃","釅","釋","釐","釓","釔",
"釕","釗","釘","釙","針","釣","釤","釦","釧","釩","釬","釵","釷","釹","釺","鈀","鈁","鈃","鈄","鈅",
"鈈","鈉","鈍","鈎","鈐","鈑","鈒","鈔","鈕","鈞","鈡","鈣","鈥","鈦","鈧","鈮","鈰","鈳","鈴","鈷",
"鈸","鈹","鈺","鈽","鈾","鈿","鉀","鉄","鉅","鉆","鉈","鉉","鉋","鉍","鉑","鉕","鉗","鉚","鉛","鉞",
"鉢","鉤","鉦","鉬","鉭","鉶","鉸","鉺","鉻","鉿","銀","銃","銅","銍","銑","銓","銕","銖","銘","銚",
"銛","銜","銠","銣","銥","銦","銨","銩","銪","銫","銬","銱","銲","銳","銷","銹","銻","銼","鋁","鋃",
"鋅","鋇","鋌","鋏","鋒","鋙","鋜","鋝","鋟","鋣","鋤","鋥","鋦","鋨","鋩","鋪","鋮","鋯","鋰","鋱",
"鋶","鋸","鋻","鋼","錁","錄","錆","錇","錈","錏","錐","錒","錕","錘","錙","錚","錛","錟","錠","錡",
"錢","錦","錨","錩","錫","錮","錯","錳","錶","錸","鍀","鍁","鍃","鍆","鍇","鍈","鍊","鍋","鍍","鍔",
"鍘","鍚","鍛","鍠","鍤","鍥","鍩","鍫","鍬","鍰","鍵","鍶","鍺","鍼","鍾","鎂","鎄","鎇","鎊","鎋",
"鎔","鎖","鎘","鎚","鎛","鎡","鎢","鎣","鎦","鎧","鎩","鎪","鎬","鎮","鎰","鎲","鎳","鎵","鎸","鎿",
"鏃","鏇","鏈","鏌","鏍","鏐","鏑","鏗","鏘","鏚","鏜","鏝","鏞","鏟","鏡","鏢","鏤","鏨","鏰","鏵",
"鏷","鏹","鏽","鐃","鐋","鐐","鐒","鐓","鐔","鐘","鐙","鐝","鐠","鐦","鐧","鐨","鐫","鐮","鐲","鐳",
"鐵","鐶","鐸","鐺","鐿","鑄","鑊","鑌","鑑","鑒","鑔","鑕","鑛","鑞","鑠","鑣","鑤","鑥","鑪","鑭",
"鑰","鑱","鑲","鑷","鑹","鑼","鑽","鑾","鑿","钁","钂","長","門","閂","閃","閆","閈","閉","開","閌",
"閎","閏","閑","閒","間","閔","閘","閙","閡","関","閣","閤","閥","閨","閩","閫","閬","閭","閱","閲",
"閶","閹","閻","閼","閽","閾","閿","闃","闆","闈","闊","闋","闌","闍","闐","闒","闓","闔","闕","闖",
"闚","關","闞","闠","闡","闢","闤","闥","阬","阯","陘","陝","陞","陣","陰","陳","陸","陽","隂","隄",
"隉","隊","階","隕","隖","際","隣","隨","險","隱","隴","隷","隸","隻","雋","雖","雙","雛","雜","雞",
"離","難","雲","電","霑","霛","霤","霧","霽","靂","靄","靆","靈","靉","靚","靜","靣","靦","靨","靭",
"鞀","鞉","鞏","鞦","鞽","韁","韃","韆","韉","韋","韌","韍","韓","韙","韜","韝","韞","韤","韻","響",
"頁","頂","頃","項","順","頇","須","頊","頌","頎","頏","預","頑","頒","頓","頗","領","頜","頡","頤",
"頦","頫","頭","頮","頰","頲","頴","頷","頸","頹","頻","頽","顆","題","額","顎","顏","顒","顓","顔",
"願","顙","顛","類","顢","顥","顧","顫","顬","顯","顰","顱","顳","顴","風","颭","颮","颯","颱","颳",
"颶","颸","颺","颻","颼","飀","飃","飄","飆","飇","飈","飛","飢","飣","飥","飩","飪","飫","飭","飯",
"飲","飴","飼","飽","飾","飿","餃","餄","餅","餉","養","餌","餎","餏","餑","餒","餓","餕","餖","餘",
"餚","餛","餜","餞","餡","館","餱","餳","餵","餶","餷","餺","餼","餽","餾","餿","饁","饃","饅","饈",
"饉","饊","饋","饌","饑","饒","饗","饜","饝","饞","饢","馬","馭","馮","馱","馳","馴","馹","駁","駐",
"駑","駒","駔","駕","駘","駙","駛","駝","駟","駡","駢","駭","駮","駰","駱","駸","駿","騁","騂","騅",
"騌","騍","騎","騏","騐","騖","騗","騙","騣","騤","騫","騭","騮","騰","騶","騷","騸","騾","驀","驁",
"驂","驃","驄","驅","驊","驌","驍","驏","驕","驗","驘","驚","驛","驟","驢","驤","驥","驦","驪","驫",
"骾","髏","髒","體","髕","髖","髩","髮","鬁","鬆","鬍","鬚","鬢","鬥","鬦","鬧","鬨","鬩","鬭","鬮",
"鬱","魎","魘","魚","魛","魢","魨","魯","魴","魷","魺","鮁","鮃","鮊","鮋","鮌","鮍","鮎","鮐","鮑",
"鮒","鮓","鮚","鮜","鮞","鮦","鮪","鮫","鮭","鮮","鮳","鮶","鮷","鮺","鯀","鯁","鯇","鯉","鯊","鯒",
"鯔","鯕","鯖","鯗","鯛","鯝","鯡","鯢","鯤","鯧","鯨","鯪","鯫","鯰","鯴","鯵","鯷","鯽","鯿","鰁",
"鰂","鰃","鰈","鰉","鰌","鰍","鰏","鰐","鰒","鰓","鰛","鰜","鰟","鰠","鰣","鰥","鰨","鰩","鰭","鰮",
"鰱","鰲","鰳","鰵","鰷","鰹","鰺","鰻","鰼","鰾","鱂","鱅","鱈","鱉","鱒","鱓","鱔","鱖","鱗","鱘",
"鱝","鱟","鱠","鱣","鱤","鱧","鱨","鱭","鱯","鱷","鱸","鱺","鳥","鳧","鳩","鳲","鳳","鳴","鳶","鴆",
"鴇","鴉","鴒","鴕","鴛","鴝","鴞","鴟","鴣","鴦","鴨","鴬","鴯","鴰","鴴","鴻","鴿","鵂","鵃","鵐",
"鵑","鵒","鵓","鵜","鵝","鵞","鵠","鵡","鵪","鵬","鵮","鵯","鵲","鵶","鵷","鵾","鶇","鶉","鶊","鶓",
"鶖","鶘","鶚","鶡","鶤","鶥","鶩","鶬","鶯","鶲","鶴","鶹","鶺","鶻","鶼","鶿","鷀","鷁","鷂","鷄",
"鷊","鷓","鷖","鷗","鷙","鷚","鷥","鷦","鷫","鷯","鷰","鷲","鷳","鷴","鷸","鷹","鷺","鷼","鸇","鸌",
"鸎","鸏","鸕","鸘","鸚","鸛","鸝","鸞","鹵","鹹","鹺","鹼","鹽","麅","麗","麥","麩","麪","麯","麵",
"麼","黃","黌","點","黨","黲","黴","黶","黷","黽","黿","鼂","鼇","鼈","鼉","鼕","鼴","齇","齊","齋",
"齎","齏","齒","齔","齕","齗","齙","齜","齟","齠","齡","齣","齦","齧","齪","齬","齲","齶","齷","龍",
"龐","龔","龕","龜"};
static const char * const SimplifiedFonts[] = {
"丢","并","乱","亘","亚","夫","伫","布","占","并","来","仑","侣","局","俣","系","侠","伥","俩","仓",
"个","们","幸","仿","伦","伟","侧","侦","偷","咱","伪","杰","伧","伞","备","效","家","佣","偬","传",
"伛","债","伤","倾","偻","仅","佥","侨","仆","伪","侥","偾","雇","价","仪","侬","亿","当","侩","俭",
"傧","俦","侪","尽","偿","优","储","俪","罗","攒","傩","傥","俨","凶","兑","儿","兖","内","两","册",
"幂","涂","冻","凛","渎","处","凯","凭","别","删","刭","则","克","刬","刚","剥","剐","剀","创","铲",
"划","札","剧","刘","刽","刿","剑","剂","剑","劲","动","勖","务","勋","胜","劳","势","绩","剿","勚",
"劢","勋","励","劝","匀","匦","汇","匮","奁","奁","椟","区","协","恤","却","厍","厅","厕","历","厌",
"厂","厉","厣","参","丛","吴","吕","呙","员","咔","呗","唣","吣","念","问","启","啖","哑","启","唡",
"衔","咱","唤","岩","丧","吃","乔","单","哟","呛","啬","唝","吗","呜","唢","哔","叹","喽","呕","啧",
"尝","唛","哗","唠","啸","叽","哓","呒","啴","恶","咴","嘘","咝","哒","哝","哕","嗳","哙","喷","吨",
"当","咛","吓","哜","尝","噜","啮","咽","呖","咙","向","亸","喾","严","嘤","嚣","啭","嗫","嚣","冁",
"呓","啰","苏","嘱","回","囱","回","国","囵","国","围","园","圆","图","团","垧","埯","坝","垭","采",
"执","坚","垩","垴","埚","阶","尧","报","场","碱","块","茔","垲","埘","涂","冢","坞","埙","场","尘",
"堑","砖","垫","坠","硗","堕","坛","坟","垯","墙","垦","坛","垱","埙","压","垒","圹","垆","坛","坏",
"垄","垄","坜","坝","塆","壮","壶","壸","寿","寿","够","梦","夹","奂","奥","奁","夺","奋","妆","姗",
"奸","侄","娱","妩","娄","妇","淫","娅","娲","偷","妫","媪","妈","袅","妪","妩","娴","娴","婳","妫",
"娆","婵","娇","嫱","袅","嫒","嬷","嫔","奶","婴","婶","懒","娘","娈","孙","学","孪","宫","寝","实",
"宁","审","写","宽","宠","宝","克","将","专","寻","对","导","尴","尴","届","尸","屃","屉","屡","层",
"屦","属","屃","冈","岘","岛","峡","崃","昆","昆","岗","仑","岽","峥","岽","嵛","岚","岁","嵝","崭",
"岖","嵚","崂","峤","峣","峄","峃","崄","岙","嵘","岭","屿","岳","岿","峦","巅","岩","巯","卺","帅",
"师","帐","带","帧","帏","帼","帻","帜","币","帮","帱","襕","干","几","库","厕","厢","厩","厦","庼",
"荫","厨","厮","庙","厂","庑","废","广","廪","庐","厅","回","乃","吊","弪","张","强","别","弹","强",
"弥","弯","汇","彝","彝","彟","彦","雕","佛","径","从","徕","复","仿","征","彻","恒","耻","悦","怅",
"闷","凄","恶","恼","恽","恻","爱","惬","悫","怆","恺","忾","栗","殷","态","愠","惨","惭","惭","恸",
"惯","悫","怄","怂","虑","悭","慑","庆","戚","欲","忧","惫","怜","凭","愦","慭","惮","愤","悯","怃",
"宪","忆","恳","应","怿","懔","恹","蒙","怼","懑","恹","惩","懒","怀","悬","忏","惧","欢","慑","恋",
"戆","戋","戗","戬","戏","战","戏","户","扦","挟","舍","扪","卷","扫","抡","挜","挣","挂","采","拣",
"扬","换","挥","背","构","揿","损","摇","捣","抢","榨","掴","掼","搂","揸","挚","抠","抟","掺","捞",
"挦","撑","挠","捻","挢","掸","拨","抚","扑","揿","挞","挝","捡","拥","掳","择","击","挡","担","携",
"据","挤","抬","捣","举","拟","摈","拧","搁","掷","扩","撷","摆","擞","撸","扰","摅","撵","拢","拦",
"撄","搀","撺","携","摄","攒","挛","摊","挡","搅","揽","考","叙","败","叙","扬","敌","数","驱","敛",
"毙","斓","斩","断","旗","升","时","晋","昼","晕","晖","旸","畅","暂","昵","晔","历","昙","晓","向",
"暧","旷","叠","昽","晒","书","会","胧","东","拐","栅","拐","杆","栀","枧","条","枭","捆","弃","枨",
"枣","栋","栈","桊","栖","梾","桠","杨","枫","桢","业","极","干","杩","荣","桤","盘","构","枪","杠",
"椠","椁","桨","规","桩","乐","枞","梁","楼","标","枢","样","丛","朴","树","桦","桡","桥","机","椭",
"横","槔","檩","柽","档","桧","槚","检","樯","梼","台","槟","柠","槛","苘","棹","柜","橹","榈","栉",
"椟","橼","栎","橱","槠","栌","枥","橥","榇","栊","榉","棂","樱","栏","权","椤","攒","栾","榄","棂",
"钦","叹","欧","啸","敛","欤","欢","岁","历","归","殁","残","殒","殇","殚","殓","殡","歼","杀","壳",
"毁","殴","医","绒","球","毵","牦","毡","毡","氇","气","氢","氩","氲","凼","泛","泛","污","污","决",
"冱","没","冲","况","泄","汹","浃","泾","莅","凉","凄","泪","渌","净","凌","沦","渊","涞","浅","涣",
"减","沨","涡","测","浑","凑","浈","愍","涌","汤","沩","准","沟","温","浉","涢","湿","沧","灭","涤",
"荥","汇","沪","滞","渗","卤","浒","浐","滚","满","渔","溇","沤","汉","涟","渍","涨","溆","渐","浆",
"颍","泼","洁","沩","潜","舄","润","浔","溃","滗","涠","涩","涩","澄","浇","涝","涧","渑","泽","滪",
"泶","浍","淀","浊","浓","沵","湿","泞","蒙","浕","济","涛","滥","浚","潍","滨","阔","溅","泺","滤",
"滢","渎","泻","渖","浏","濒","泸","沥","潇","潆","潴","泷","濑","弥","潋","澜","沣","滠","洒","漓",
"滩","灏","湾","滦","滟","滟","灾","照","为","乌","烃","无","煅","辉","炼","炜","暖","烟","茕","焕",
"烦","炀","荧","炝","热","颎","炽","烨","焰","灯","炖","磷","烧","烫","焖","营","灿","毁","烛","烩",
"熏","烬","焘","耀","烁","炉","烨","烂","争","为","爷","尔","床","墙","笺","闸","牍","抵","牵","荦",
"牦","犊","牺","状","狭","狈","狰","犹","狲","犸","呆","狱","狮","奖","独","狯","猃","狝","狞","获",
"猎","犷","兽","獭","献","猕","猡","兹","珏","佩","现","璃","管","珐","珲","珉","玮","玚","琐","瑶",
"莹","玛","琅","玱","琏","琎","玑","瑷","珰","环","玙","玺","璇","琼","珑","璎","瓒","瓯","砖","瓮",
"罂","产","产","苏","亩","毕","画","异","留","当","畴","叠","痉","酸","痹","痖","愈","疯","疡","痪",
"瘗","疮","疟","瘆","瘘","瘘","疗","痨","痫","瘅","愈","疠","瘪","痴","痒","疖","症","疬","癞","癣",
"瘿","瘾","痈","瘫","癫","发","皑","疱","皲","皱","杯","盗","盏","尽","监","盘","卢","荡","视","视",
"眦","众","困","睁","睐","眍","瞒","睑","蒙","眬","瞩","矫","炮","朱","硁","硖","砗","砚","碜","硕",
"砀","砜","确","码","硙","砖","碜","碛","矶","硗","硚","础","碍","矿","砺","砾","矾","炮","砻","佑",
"秘","禄","祸","祯","祎","御","禅","礼","祢","祷","秃","籼","税","秆","棱","禀","秸","种","称","谷",
"稣","积","颖","秾","穑","秽","颓","稳","获","稆","窝","洼","穷","窑","窑","窭","窥","窜","窍","窦",
"灶","窃","并","竖","竞","笔","笋","笕","个","笺","筝","棰","节","范","筑","箧","箬","筱","笃","筛",
"筚","箦","篓","蓑","箪","简","篑","箫","檐","筜","签","帘","篮","筹","藤","箓","箨","籁","笼","奁",
"签","钥","笾","簖","篱","箩","吁","妆","曲","粤","糁","粪","模","粮","团","粝","籴","粜","纠","纪",
"纣","约","红","纡","纥","纨","纫","纹","纳","纽","纾","纯","纰","纼","纱","纮","纸","级","纷","纭",
"纴","纺","扎","扎","细","绂","绁","绅","纻","绍","绀","绋","绐","绌","终","弦","组","绊","纴","绗",
"绁","结","绝","绦","绔","绞","络","绚","给","绒","绖","统","丝","绛","绢","绑","绡","绠","绨","绣",
"绤","绥","捆","经","综","缍","绿","绸","绻","线","绶","维","绹","绾","纲","网","绷","缀","彩","纶",
"绺","绮","绽","绰","绫","绵","绲","缁","紧","绯","缗","绪","绬","绱","缃","缄","缂","线","绵","缉",
"缎","缔","缗","缘","绁","缌","编","缓","缅","纬","缑","缈","练","缏","缇","致","缊","总","萦","缙",
"缢","缒","绉","缣","缊","缞","绦","缚","缜","缟","缛","县","绦","缝","缡","缩","演","纵","缧","纤",
"缦","絷","缕","缥","总","绩","绷","缫","缪","襁","缯","织","缮","伞","翻","缭","绕","绣","缋","襁",
"绳","绘","系","茧","缰","缳","缲","缴","绎","继","缤","缱","颣","缬","纩","续","累","缠","缨","纤",
"缵","缆","钵","坛","瓮","罂","坛","垆","罚","骂","罢","罚","罗","罴","羁","芈","绒","羟","羡","义",
"膻","习","翚","翘","翱","翙","端","锄","耧","耢","圣","闻","联","聪","声","耸","聩","聂","职","聍",
"听","听","聋","肃","胁","胁","脉","胫","唇","修","脱","胀","肾","胨","脶","脑","肿","脚","肠","肷",
"腽","腘","肤","胶","腻","胆","脍","脓","脸","脐","膑","癯","腊","胪","脏","脔","臜","卧","临","皋",
"台","与","兴","举","旧","铺","馆","舱","樯","橹","舣","舰","橹","舻","艰","艳","艹","刍","苎","兹",
"荆","庄","茎","荚","苋","华","庵","苌","莱","万","莴","叶","荭","参","荮","苇","药","荤","搜","莼",
"莳","莅","苍","荪","席","盖","参","莜","莲","苁","莼","荜","菱","卜","蒌","蒋","葱","茑","荫","麻",
"荨","蒇","荞","荬","芸","莸","荛","蒉","荡","芜","萧","蓣","荟","蓟","芗","姜","蔷","荙","莶","荐",
"萨","荠","蓝","荩","艺","药","薮","苈","蔼","蔺","萚","蕲","芦","苏","蕴","苹","藓","蔹","茏","兰",
"蓠","萝","处","虚","虏","号","亏","虬","蛱","蜕","蚬","蚀","猬","虾","虱","蜗","蛳","蚁","蚂","萤",
"蝼","螀","蛰","蝈","螨","虮","蝉","蛲","虫","蛏","蚁","蝇","虿","蝎","蛴","蝾","蚝","蜡","蛎","蟏",
"蛊","蚕","蛮","众","蔑","术","胡","卫","冲","卫","只","衮","袅","夹","里","补","装","里","制","复",
"裈","袆","裤","裢","褛","亵","幞","裥","杂","袯","袄","裣","裆","褴","袜","衬","袭","襕","核","见",
"觃","规","觅","觅","视","觇","眺","觋","觍","觎","亲","觊","觏","觑","觐","觑","觉","觑","览","觌",
"观","抵","觞","觯","触","讠","订","讣","计","讯","讧","讨","吁","讦","讱","训","讪","讫","托","记",
"讹","讶","讼","欣","诀","讷","谌","讻","访","设","许","诉","诃","诊","注","证","诂","诋","讵","诈",
"诒","诏","评","诐","诇","诎","诅","词","咏","诩","询","诣","试","诗","诧","诟","诡","诠","诘","话",
"该","详","诜","诙","讻","诖","诔","诛","诓","夸","志","认","诳","诶","诞","诱","诮","语","诚","诫",
"诬","误","诰","诵","诲","说","说","谁","课","谇","诽","谊","调","谄","谆","谈","诿","请","诤","诹",
"诼","谅","论","谂","谀","谍","谞","谝","谥","诨","谔","谛","谐","谏","谕","谘","讳","谙","谌","讽",
"诸","谚","谖","诺","谋","谒","谓","誊","诌","谎","谜","谧","谑","谡","谤","谦","谥","讲","谢","谣",
"谟","谪","谬","讴","谨","谩","哗","嘻","证","讹","谲","讥","谮","识","谯","谭","谱","噪","谵","毁",
"译","议","谴","护","诪","誉","谫","读","谪","审","变","詟","燕","雠","雠","谗","让","谰","谶","赞",
"呓","谠","谳","溪","岂","竖","丰","艳","猪","豮","狸","猫","贝","贞","贠","负","财","贡","贫","货",
"贩","贪","贯","责","贮","贳","赀","贰","贵","贬","买","贷","贶","费","贴","贻","贸","贺","贲","赂",
"赁","贿","赅","资","贾","恤","贼","赃","赈","赊","宾","宾","赇","赒","赉","赞","赐","赏","赔","赓",
"贤","卖","贱","赋","赕","质","赍","账","赌","赆","赖","赗","剩","赚","赙","购","赛","赜","贽","赘",
"赟","赠","赞","赝","赡","赢","赆","赃","赑","赎","赝","赣","赃","赪","赶","赵","趋","趱","迹","局",
"践","蜷","踊","跄","跸","迹","跖","蹒","踪","跷","跶","趸","踌","跻","跃","踯","跞","踬","蹰","跹",
"蹑","蹿","躜","躏","体","躯","亸","车","轧","轨","军","轪","轩","轫","轭","软","轷","轸","轱","轴",
"轵","轺","轲","轶","轼","较","辂","辁","辀","载","轾","辄","挽","辅","轻","辆","辎","辉","辋","辍",
"辊","辇","辈","轮","辌","软","辑","辏","输","辐","辒","辗","舆","辒","毂","辖","辕","辘","转","辙",
"轿","辚","轰","辔","轹","轳","辞","办","辞","辫","辩","农","农","迤","回","乃","径","这","连","周",
"进","游","运","过","达","违","遥","逊","沓","递","远","适","迟","迁","选","遗","辽","迈","还","迩",
"边","逻","逦","合","郏","郄","邮","郓","乡","邹","邬","乡","郧","墉","邓","郑","邻","郸","邺","郐",
"邝","郦","酬","腌","酝","丑","酝","医","酱","酦","酬","燕","酿","衅","酾","酽","释","厘","钆","钇",
"钌","钊","钉","钋","针","钓","钐","扣","钏","钒","焊","钗","钍","钕","钎","钯","钫","钘","钭","钥",
"钚","钠","钝","钩","钤","钣","钑","钞","钮","钧","钟","钙","钬","钛","钪","铌","铈","钶","铃","钴",
"钹","铍","钰","钸","铀","钿","钾","铁","钜","钻","铊","铉","刨","铋","铂","钷","钳","铆","铅","钺",
"钵","钩","钲","钼","钽","铏","铰","铒","铬","铪","银","铳","铜","铚","铣","铨","铁","铢","铭","铫",
"铦","衔","铑","铷","铱","铟","铵","铥","铕","铯","铐","铞","焊","锐","销","锈","锑","锉","铝","锒",
"锌","钡","铤","铗","锋","铻","镯","锊","锓","铘","锄","锃","锔","锇","铓","铺","铖","锆","锂","铽",
"锍","锯","鉴","钢","锞","录","锖","锫","锩","铔","锥","锕","锟","锤","锱","铮","锛","锬","锭","锜",
"钱","锦","锚","锠","锡","锢","错","锰","表","铼","锝","锨","锪","钔","锴","锳","炼","锅","镀","锷",
"铡","钖","锻","锽","锸","锲","锘","锹","锹","锾","键","锶","锗","针","钟","镁","锿","镅","镑","辖",
"镕","锁","镉","锤","镈","镃","钨","蓥","镏","铠","铩","锼","镐","镇","镒","镋","镍","镓","镌","镎",
"镞","旋","链","镆","镙","镠","镝","铿","锵","戚","镗","镘","镛","铲","镜","镖","镂","錾","镚","铧",
"镤","镪","锈","铙","铴","镣","铹","镦","镡","钟","镫","镢","镨","锎","锏","镄","镌","镰","镯","镭",
"铁","镮","铎","铛","镱","铸","镬","镔","鉴","鉴","镲","锧","矿","镴","铄","镳","刨","镥","炉","镧",
"钥","镵","镶","镊","镩","锣","钻","銮","凿","镢","镋","长","门","闩","闪","闫","闬","闭","开","闶",
"闳","闰","闲","闲","间","闵","闸","闹","阂","关","阁","合","阀","闺","闽","阃","阆","闾","阅","阅",
"阊","阉","阎","阏","阍","阈","阌","阒","板","闱","阔","阕","阑","阇","阗","阘","闿","阖","阙","闯",
"窥","关","阚","阓","阐","辟","阛","闼","坑","址","陉","陕","升","阵","阴","陈","陆","阳","阴","堤",
"陧","队","阶","陨","坞","际","邻","随","险","隐","陇","隶","隶","只","隽","虽","双","雏","杂","鸡",
"离","难","云","电","沾","灵","溜","雾","霁","雳","霭","叇","灵","叆","靓","静","面","腼","靥","韧",
"鼗","鼗","巩","秋","鞒","缰","鞑","千","鞯","韦","韧","韨","韩","韪","韬","鞴","韫","袜","韵","响",
"页","顶","顷","项","顺","顸","须","顼","颂","颀","颃","预","顽","颁","顿","颇","领","颌","颉","颐",
"颏","俯","头","颒","颊","颋","颕","颔","颈","颓","频","颓","颗","题","额","颚","颜","颙","颛","颜",
"愿","颡","颠","类","颟","颢","顾","颤","颥","显","颦","颅","颞","颧","风","飐","飑","飒","台","刮",
"飓","飔","扬","飖","飕","飗","飘","飘","飙","飙","飚","飞","饥","饤","饦","饨","饪","饫","饬","饭",
"饮","饴","饲","饱","饰","饳","饺","饸","饼","饷","养","饵","饹","饻","饽","馁","饿","馂","饾","余",
"肴","馄","馃","饯","馅","馆","糇","饧","喂","馉","馇","馎","饩","馈","馏","馊","馌","馍","馒","馐",
"馑","馓","馈","馔","饥","饶","飨","餍","馍","馋","馕","马","驭","冯","驮","驰","驯","驲","驳","驻",
"驽","驹","驵","驾","骀","驸","驶","驼","驷","骂","骈","骇","驳","骃","骆","骎","骏","骋","骍","骓",
"骔","骒","骑","骐","验","骛","骗","骗","鬃","骙","骞","骘","骝","腾","驺","骚","骟","骡","蓦","骜",
"骖","骠","骢","驱","骅","骕","骁","骣","骄","验","骡","惊","驿","骤","驴","骧","骥","骦","骊","骉",
"鲠","髅","脏","体","髌","髋","鬓","发","疬","松","胡","须","鬓","斗","斗","闹","哄","阋","斗","阄",
"郁","魉","魇","鱼","鱽","鱾","鲀","鲁","鲂","鱿","鲄","鲅","鲆","鲌","鲉","鲧","鲏","鲇","鲐","鲍",
"鲋","鲊","鲒","鲘","鲕","鲖","鲔","鲛","鲑","鲜","鲓","鲪","鳀","鲝","鲧","鲠","鲩","鲤","鲨","鲬",
"鲻","鲯","鲭","鲞","鲷","鲴","鲱","鲵","鲲","鲳","鲸","鲮","鲰","鲶","鲺","鲹","鳀","鲫","鳊","鳈",
"鲗","鳂","鲽","鳇","鳅","鳅","鲾","鳄","鳆","鳃","鳁","鳒","鳑","鳋","鲥","鳏","鳎","鳐","鳍","鳁",
"鲢","鳌","鳓","鳘","鲦","鲣","鲹","鳗","鳛","鳔","鳉","鳙","鳕","鳖","鳟","鳝","鳝","鳜","鳞","鲟",
"鲼","鲎","鲙","鳣","鳡","鳢","鲿","鲚","鳠","鳄","鲈","鲡","鸟","凫","鸠","鸤","凤","鸣","鸢","鸩",
"鸨","鸦","鸰","鸵","鸳","鸲","鸮","鸱","鸪","鸯","鸭","鸴","鸸","鸹","鸻","鸿","鸽","鸺","鸼","鹀",
"鹃","鹆","鹁","鹈","鹅","鹅","鹄","鹉","鹌","鹏","鹐","鹎","鹊","鸦","鹓","鹍","鸫","鹑","鹒","鹋",
"鹙","鹕","鹗","鹖","鹍","鹛","鹜","鸧","莺","鹟","鹤","鹠","鹡","鹘","鹣","鹚","鹚","鹢","鹞","鸡",
"鹝","鹧","鹥","鸥","鸷","鹨","鸶","鹪","鹔","鹩","燕","鹫","鹇","鹇","鹬","鹰","鹭","鹇","鹯","鹱",
"莺","鹲","鸬","鹴","鹦","鹳","鹂","鸾","卤","咸","鹾","碱","盐","狍","丽","麦","麸","面","曲","面",
"么","黄","黉","点","党","黪","霉","黡","黩","黾","鼋","鼌","鳌","鳖","鼍","冬","鼹","齄","齐","斋",
"赍","齑","齿","龀","龁","龂","龅","龇","龃","龆","龄","出","龈","啮","龊","龉","龋","腭","龌","龙",
"庞","龚","龛","龟"};

}

#endif

