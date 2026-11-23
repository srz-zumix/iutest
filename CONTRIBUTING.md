# 貢献方法

1. フォークする
1. feature branch を作る
1. 変更するを commit する
1. push
1. プルリクする
1. CI の結果を確認する（重要なのは GitHub Actions です。それ以外は気にしなくて良いです）

fork からのプルリクエストでは、Docker Hub の認証情報が必要なジョブや書き込み権限が必要な一部の処理がスキップされます。
それ以外のテストや lint は引き続き実行されます。
JUnit の結果は、別のチェックではなくジョブの注釈とサマリーに表示されます。

----

# How To Contribute

1. Fork it ( https://github.com/srz-zumix/iutest )
1. Create your feature branch (git checkout -b my-new-feature)
1. Commit your changes (git commit -am 'Add some feature')
1. Push to the branch (git push origin my-new-feature)
1. Create new Pull Request
1. Please check the result of CI (Important is GitHub Actions. Other than that, you do not have to worry)

For pull requests from forks, jobs requiring Docker Hub credentials and some operations requiring write permissions are skipped.
Other tests and linters continue to run.
JUnit results appear as job annotations and summaries instead of a separate check.
