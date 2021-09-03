# M5StickC_MechanumCar
M5StickC Easy Mechanum Wheel controller

<img width="1776" alt="over view" src="https://user-images.githubusercontent.com/52347942/131996220-383bbee7-ef68-42dd-9b68-57af712bb7aa.png">

# Features

* https://www.youtube.com/embed/BKFsxIaVx48


# システム構成
## Atmega328（メカナムホイール車体）
* 全長25cmの大型な車体サイズ
* 前後左右、回転など11種類の動作モードを搭載
* Atmega328から２個のモータドライバを介してメカナムホイールを制御
* モータの駆動電力には○イソーの500円モバイルバッテリを使用
* フロントとリアにそれぞれ10個のNeopixelを搭載し、コマンドに応じた点灯パタンを実現

## M5Stick C（レシーバ）
* ESP-NOWによりリモートコントローラからのコマンドを受信
* M5StickCからI2C接続により、車両本体のAtmega328を制御

## M5Stick CPlus（コントローラ）
* ジョイスティックと２種類のボタンによるコマンド入力
* ESP-NOWによりM5Stick Cに前後左右、回転など10種類のコマンドを送信


