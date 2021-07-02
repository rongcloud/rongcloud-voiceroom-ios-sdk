
Pod::Spec.new do |s|


    s.name         = "RCVoiceRoomLib"
    s.version      = "0.9.1"
    s.summary      = "Rong Cloud Voice Room Lib."


    s.description  = <<-DESC
                        Rong Cloud Voice Room Lib for iOS.
                        DESC


    s.homepage     = "https://www.rongcloud.cn/"
    s.license      = { :type => "Copyright", :text => "Copyright 2021 RongCloud" }
    s.author             = { "zangqilong" => "https://www.rongcloud.cn/" }
    s.social_media_url   = "https://www.rongcloud.cn/"
    s.platform     = :ios, "9.0"
    s.source           = { :git => 'https://github.com/rongcloud/rongcloud-voiceroom-ios-sdk.git', :tag => s.version.to_s }
    s.requires_arc = true
    s.static_framework = true
    s.pod_target_xcconfig = {
        'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64'
    }
    s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }

    s.vendored_frameworks = 'RCVoiceRoomLib.xcframework'

    s.dependency 'RongCloudRTC/RongRTCLib', '5.1.2.1'
    s.dependency 'RongCloudIM/IMLib', '5.1.2.1'

end

