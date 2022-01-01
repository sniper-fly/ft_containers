# ft_containers

## 作業計画
11/15 ~ 21 題意の把握。nfukadaさんの資料や[江添亮の入門C++](https://cpp.rainy.me/)を参考に
まずはvectorを実装する  
~~11/22 ~ 28 課題に合わせてvectorの実装~~  
11/22 ~ 28 STLを部分的に用いてvectorを実装  
~~11/29 ~ 12/5 stackの実装~~  
11/29 ~ 12/5 結合テストの実装と依存している機能の開発  
12/6 ~ 13 stackの実装  
12/14 ~ 28 mapの実装  

12/31 ~ 1/3 境界値テストの追加、reverse ite, iterator_traits
1/4 ~ 1/6   見直し vector完成
1/7 ~ 1/10  stack
1/11 ~ 1/13 赤黒木の理解
1/14 ~ 1/17 mapの実装方針

## ブランチ運用
masterとdevelopで運用  
基本developで開発し、単位ごとにPRを作って、他の人に差分をわかりやすく示す  

## CI
github actionsやpre hookを使用してPR作成時、push時に自動テストが走るようにする
