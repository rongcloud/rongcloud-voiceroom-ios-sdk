Pod::Spec.new do |s|
s.name             = 'RCVoiceRoomLib'
s.version          = '2.1.2'
s.summary          = 'Voice Room by RC IM & RTC'

s.description      = "Voice Room by RC IM & RTC @scene SDK"

s.homepage         = 'https://github.com/rongcloud'
s.author           = { 'shaoshuai' => 'shaoshuai@rongcloud.cn' }
s.license      = { :type => "Copyright", :text => "Copyright 2021 RongCloud" }
s.source           = { :git => 'https://github.com/rongcloud/rongcloud-voiceroom-ios-sdk.git', :tag => s.version.to_s }

s.ios.deployment_target = '9.0'

s.requires_arc = true

s.pod_target_xcconfig = {
'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64',
'VALID_ARCHS' =>  'arm64 armv7 x86_64',
}

s.vendored_frameworks = 'RCVoiceRoomLib.xcframework'

s.dependency 'RongCloudRTC/RongRTCLib'
s.dependency 'RongCloudIM/ChatRoom'

end
