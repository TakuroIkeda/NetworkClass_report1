add_library(report1_1
  SHARED
    simulate.c
  )
# greetingライブラリのインクルードディレクトリを教えてあげる
# PROJECT_SOURCE_DIRはこのプロジェクトのルートディレクトリの絶対パス
target_include_directories(report1_1
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
