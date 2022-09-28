
Pod::Spec.new do |s|
  s.name             = 'RCVoiceRoomLib'
  s.version          = '2.1.1'
  s.summary          = 'Voice Room by RC IM & RTC'

  s.description      = "Voice Room by RC IM & RTC @scene SDK"

  s.homepage         = 'https://github.com/rongcloud/RCVoiceRoomLib'
  s.author           = { 'shaoshuai' => 'shaoshuai@rongcloud.cn' }
  s.source           = { :git => 'https://github.com/rongcloud/RCVoiceRoomLib.git', :tag => s.version.to_s }

  s.ios.deployment_target = '11.0'
  
  s.pod_target_xcconfig = {
    'VALID_ARCHS' => 'arm64 x86_64',
    'ENABLE_BITCODE' => 'NO'
  }

  s.source_files = 'RCVoiceRoomLib/Source/Classes/**/*'
  
  s.resource_bundles = {
    'RCVoiceRoomLib' => ['RCVoiceRoomLib/Source/Assets/*']
  }

  s.public_header_files = 'Pod/Classes/Header/RCVoiceRoomLib.h'
  
  s.dependency 'RongCloudRTC/RongRTCLib'
  s.dependency 'RongCloudIM/ChatRoom'
  
end
