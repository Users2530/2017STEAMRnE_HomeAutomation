# 2017 STEAM R&E Project Repository

## Introduction : 개요

 2017 STEAM Research & Education Project<br>
 Subject : Bio-signal based Home Automation via Arduino and Raspberry pi

 This is the source code used in our 2017 STEAM R&E project.<br>
 For more infomation, see [here](https://ittms.blogspot.com/2017/12/bio-signal-based-home-automation-using.html).

 2017년도 STEAM R&E<br>
 주제: 수면 시 생체신호 변화를 이용한 홈 오토메이션 제어

 STEAM R&E 연구 중 사용한 소스 코드입니다.<br>
 본 연구에 대한 자세한 설명은 [여기(영어)](https://ittms.blogspot.com/2017/12/bio-signal-based-home-automation-using.html)를 참조하십시오.


## Hardware Design : 설계도

 <img src=design.png>

 This is the design of data collecting device.<br>
 측정기의 설계도입니다.

## About the files : 각 파일 설명

### [Arduino/](Arduino/)

 The code for the Arduinos. Upload these to the Arduinos.<br>
 이 폴더 내의 파일을 전부 다운로드한 다음, 아두이노에 업로드합니다.

 - [STEAMRnE_34A.ino](Arduino/STEAMRnE_34A.ino): The code for the Data collecting device.<br>
 데이터 수집 장치에 사용하는 코드입니다.
 - [STEAMRnE_34C.ino](Arduino/STEAMRnE_34C.ino): The code for the Control device.<br>
 전자기기 제어 장치에 사용하는 코드입니다.

### [Raspberry_Pi/](Raspberry_Pi/)

 Download and run these in your Raspberry Pi.<br>
 이 파일을 전부 다운로드한 다음, 라즈베리 파이에서 사용합니다.

 - [test.py](Raspberry_Pi/test.py): The main raspberry pi code.<br>
 파이썬 메인 코드입니다.

## [Changelog : 변경 기록(영어)](Changelog.md)
