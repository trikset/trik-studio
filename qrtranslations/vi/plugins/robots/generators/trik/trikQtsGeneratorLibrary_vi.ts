<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="vi_VN">
<context>
    <name>QObject</name>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsControlFlowValidator.cpp" line="37"/>
        <source>There is nothing to generate, diagram doesn&apos;t have Initial Node</source>
        <translation>Không có gì để tạo, sơ đồ không có nút Bắt đầu</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="141"/>
        <source>Trying to join a thread with an unknown id. Possible causes: calling fork from a subprogram or trying to merge two threads without a join</source>
        <translation>Đang cố gắng nối vào một luồng với mã định danh không xác định. Các nguyên nhân có thể: gọi fork từ một chương trình con hoặc cố gắng nối hai luồng mà không có khối join</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="148"/>
        <source>Join block must have exactly one outgoing link</source>
        <translation>Khối nối phải có đúng một liên kết đi ra</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="154"/>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="199"/>
        <source>Guard property of a link outgoing from a join must contain an id of one of joined threads</source>
        <translation>Thuộc tính bảo vệ của liên kết đi ra từ khối nối phải chứa mã định danh của một trong các luồng đã nối</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="161"/>
        <source>Joining threads in a loop is forbidden</source>
        <translation>Không được phép nối các luồng trong vòng lặp</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="223"/>
        <source>Trying to fork from a thread with an unknown id. Possible causes: calling fork from a subprogram or trying to merge two threads without a join</source>
        <translation>Đang cố tạo luồng từ một luồng có mã định danh không xác định. Các nguyên nhân có thể: gọi fork từ một chương trình con hoặc cố nối hai luồng mà không có khối Join</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="229"/>
        <source>Fork block must have at least TWO outgoing links</source>
        <translation>Khối Phân nhánh phải có ít nhất HAI liên kết đi ra</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="258"/>
        <source>Links outgoing from a fork block must have different thread ids</source>
        <translation>Các liên kết đi ra từ khối Phân nhánh phải có mã định danh luồng khác nhau</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="273"/>
        <source>Fork block must have a link marked with an id of a thread from which the fork is called, &apos;%1&apos; in this case</source>
        <translation>Khối Phân nhánh phải có một liên kết được đánh dấu bằng mã định danh của luồng mà từ đó fork được gọi, trong trường hợp này là &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="284"/>
        <source>Trying to create a thread with an already occupied id &apos;%1&apos;</source>
        <translation>Đang cố tạo một luồng với mã định danh &apos;%1&apos; đã được sử dụng</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="294"/>
        <source>Creation of threads in a cycle is forbidden, check for links to before a fork</source>
        <translation>Không được phép tạo luồng trong chu trình, hãy kiểm tra các liên kết dẫn đến khối trước khối Phân nhánh</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/threadsValidator.cpp" line="330"/>
        <source>Outgoing link is not connected</source>
        <translation>Liên kết đi ra chưa được kết nối</translation>
    </message>
</context>
<context>
    <name>trik::qts::TrikQtsGeneratorPluginBase</name>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="73"/>
        <source>Network operation timed out</source>
        <translation>Hết thời gian kết nối mạng, hãy kiểm tra cài đặt và đảm bảo robot đã được bật</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="100"/>
        <source>Casing model mismatch, check TRIK Studio settings, &quot;Robots&quot; page. It seems that TRIK casing version selected in TRIK Studio differs from version on robot.</source>
        <translation>Mô hình vỏ robot không khớp, hãy kiểm tra cài đặt trong TRIK Studio, trang &quot;Robot&quot;. Có vẻ như phiên bản vỏ TRIK đã chọn trong TRIK Studio khác với phiên bản trên robot.</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="109"/>
        <source>Generate TRIK code</source>
        <translation>Tạo mã JavaScript</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="116"/>
        <source>Upload program</source>
        <translation>Tải chương trình lên</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="123"/>
        <source>Run program</source>
        <translation>Tải và thực thi chương trình</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="130"/>
        <source>Stop robot</source>
        <translation>Dừng robot</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="146"/>
        <source>Generate TRIK Code</source>
        <translation>Tạo mã JavaScript cho TRIK</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="147"/>
        <source>Upload TRIK Program</source>
        <translation>Tải chương trình TRIK</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="148"/>
        <source>Run TRIK Program</source>
        <translation>Thực thi chương trình TRIK</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="149"/>
        <source>Stop TRIK Robot</source>
        <translation>Dừng thực thi chương trình cho TRIK</translation>
    </message>
    <message>
        <location filename="../../../../../../plugins/robots/generators/trik/trikQtsGeneratorLibrary/src/trikQtsGeneratorPluginBase.cpp" line="221"/>
        <source>There are no files to upload. You must open or generate at least one *.js or *.py file.</source>
        <translation>Không có tệp nào để tải lên. Bạn phải mở hoặc tạo ít nhất một tệp *.js hoặc *.py.</translation>
    </message>
</context>
</TS>
