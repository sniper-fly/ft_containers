## 注意点、問題分和訳要約
- namespaceはftにしなさい
- main.cppでテストを作るときは、実際のコンテナも使って比較してね！
- テストのときは時間を測ろう（２０倍までOK）
- メンバ関数、非メンバ関数のオーバーロードも求められてるよ
- もろもろの名前は本家と一緒で
- std::allocatorを使え
- 内部のデータ構造はちゃんとアルゴリズム使ってね
- iteratorがあったらちゃんと実装しよう
- iterators_traits, reverse_iterator, enable_if, is_integral, equal/lexicographical compare, std::pair, std::make_pair を再実装しよう
- publicに余計な関数はいれちゃだめ。入れるときはprivateかprotectedで
- 非メンバ関数のオーバーロードでのみfriendが許可されているよ
- `vector<bool>`のための最適化はやらなくていいよ
- stackクラスはデフォルトで内部にvectorを使っていいよ。オプションとして、他のSTLのコンテナを内部で使えるように変更する必要があるよ
