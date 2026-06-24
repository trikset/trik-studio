<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="vi_VN">
<context>
    <name>QObject</name>
    <message>
        <source>AbstractNode</source>
        <translation>Khối cơ sở</translation>
    </message>
    <message>
        <source>Clear Screen</source>
        <translation>Xóa màn hình</translation>
    </message>
    <message>
        <source>Clears everything drawn on the robot`s screen.</source>
        <translation>Xóa mọi thứ đã vẽ trên màn hình robot.</translation>
    </message>
    <message>
        <source>Redraw</source>
        <translation>Vẽ lại hình ảnh</translation>
    </message>
    <message>
        <source>Comment</source>
        <translation>Ghi chú</translation>
    </message>
    <message>
        <source>This block can hold text notes that are ignored by generators and interpreters. Use it for improving the diagram readability.</source>
        <translation>Khối này có thể chứa các ghi chú văn bản mà trình tạo mã và trình thông dịch sẽ bỏ qua. Sử dụng nó để cải thiện tính dễ đọc của sơ đồ.</translation>
    </message>
    <message>
        <source>Enter some text here...</source>
        <translation>Nhập văn bản tại đây...</translation>
    </message>
    <message>
        <source>Link</source>
        <translation>Đường nối</translation>
    </message>
    <message>
        <source>For creating a link between two elements A and B you can just hover a mouse above A, press the right mouse button and (without releasing it) draw a line to the element B. Alternatively you can just &apos;pull&apos; a link from a small blue circle next to the element.</source>
        <translation>Để tạo liên kết giữa hai phần tử A và B, bạn có thể di chuột lên A, nhấn nút chuột phải và (mà không nhả ra) kéo đường nối đến phần tử B. Hoặc bạn có thể &apos;kéo&apos; một liên kết từ vòng tròn xanh nhỏ bên cạnh phần tử.</translation>
    </message>
    <message>
        <source>Guard</source>
        <translation>Điều kiện</translation>
    </message>
    <message>
        <source>EngineCommand</source>
        <translation>Khối cơ sở điều khiển động cơ</translation>
    </message>
    <message>
        <source>EngineMovementCommand</source>
        <translation>Khối cơ sở bật động cơ</translation>
    </message>
    <message>
        <source>100</source>
        <translation>100</translation>
    </message>
    <message>
        <source>Power (%)</source>
        <translation>Công suất (%)</translation>
    </message>
    <message>
        <source>End if</source>
        <translation>Kết thúc điều kiện</translation>
    </message>
    <message>
        <source>Unites control flow from different condition branches.</source>
        <translation>Gộp các nhánh điều khiển từ các nhánh điều kiện khác nhau.</translation>
    </message>
    <message>
        <source>Final Node</source>
        <translation>Kết thúc</translation>
    </message>
    <message>
        <source>The final node of the program. If the program consists of some parallel execution lines the reachment of this block terminates the corresponding execution line. This block can`t have outgoing links.</source>
        <translation>Nút cuối cùng của chương trình. Nếu chương trình gồm nhiều luồng thực thi song song, việc đến được khối này sẽ kết thúc luồng thực thi tương ứng. Khối này không thể có liên kết đi ra.</translation>
    </message>
    <message>
        <source>Fork</source>
        <translation>Nhiệm vụ song song</translation>
    </message>
    <message>
        <source>Separates program execution into a number of threads that will be executed concurrently from the programmers`s point of view. For example in such way signal from sensor and some time interval can be waited synchroniously. This block must have at least two outgoing links. &apos;Guard&apos; property of every link must contain unique thread identifiers, and one of those identifiers must be the same as the identifier of a thread where fork is placed (it must be &apos;main&apos; if it is the first fork in a program.</source>
        <translation>Tách việc thực thi chương trình thành nhiều luồng sẽ được thực hiện đồng thời theo quan điểm của lập trình viên. Ví dụ, theo cách này, có thể đồng thời chờ tín hiệu từ cảm biến và một khoảng thời gian. Khối này phải có ít nhất hai liên kết đi ra. Thuộc tính &apos;Điều kiện&apos; của mỗi liên kết phải chứa các định danh luồng duy nhất, và một trong các định danh đó phải giống với định danh của luồng nơi đặt khối fork (phải là &apos;main&apos; nếu đây là khối fork đầu tiên trong chương trình.</translation>
    </message>
    <message>
        <source>Expression</source>
        <translation>Biểu thức</translation>
    </message>
    <message>
        <source>Evaluates a value of the given expression. Also new variables can be defined in this block. See the &apos;Expressions Syntax&apos; chapter in help for more information about &apos;Function&apos; block syntax.</source>
        <translation>Tính giá trị của biểu thức đã cho. Cũng có thể định nghĩa các biến mới trong khối này. Xem chương &apos;Cú pháp biểu thức&apos; trong phần trợ giúp để biết thêm thông tin về cú pháp khối &apos;Hàm&apos;.</translation>
    </message>
    <message>
        <source>Expression:</source>
        <translation>Biểu thức:</translation>
    </message>
    <message>
        <source>Get Button Code</source>
        <translation>Lấy mã nút bấm</translation>
    </message>
    <message>
        <source>Assigns a given variable a value of pressed button. If no button is pressed at the moment and &apos;Wait&apos; property is false when variable is set to -1.</source>
        <translation>Gán cho biến đã cho giá trị của nút bấm được nhấn. Nếu không có nút nào được nhấn tại thời điểm đó và thuộc tính &apos;Đợi&apos; là sai thì biến sẽ được đặt thành -1.</translation>
    </message>
    <message>
        <source>Variable:</source>
        <translation>Biến:</translation>
    </message>
    <message>
        <source>Wait:</source>
        <translation>Đợi nhấn:</translation>
    </message>
    <message>
        <source>x</source>
        <translation>x</translation>
    </message>
    <message>
        <source>Variable</source>
        <translation>Biến</translation>
    </message>
    <message>
        <source>Wait</source>
        <translation>Chờ</translation>
    </message>
    <message>
        <source>Condition</source>
        <translation>Điều kiện</translation>
    </message>
    <message>
        <source>Separates program execution in correspondece with the given condition. The &apos;Condition&apos; parameter value must be some boolean expression that will determine subsequent program execution line. This block must have two outgoing links, at least one of them must have &apos;Guard&apos; parameter set to &apos;true&apos; or &apos;false&apos;. The execution will be proceed trough the link marked with the guard corresponding to &apos;Condition&apos; parameter of the block.</source>
        <translation>Tách việc thực thi chương trình theo điều kiện đã cho. Giá trị tham số &apos;Điều kiện&apos; phải là một biểu thức logic sẽ xác định luồng thực thi tiếp theo của chương trình. Khối này phải có hai liên kết đi ra, ít nhất một trong số đó phải có tham số &apos;Điều kiện&apos; được đặt là &apos;đúng&apos; hoặc &apos;sai&apos;. Việc thực thi sẽ tiếp tục qua liên kết được đánh dấu bằng điều kiện tương ứng với tham số &apos;Điều kiện&apos; của khối.</translation>
    </message>
    <message>
        <source>Condition:</source>
        <translation>Điều kiện:</translation>
    </message>
    <message>
        <source>x &gt; 0</source>
        <translation>x &gt; 0</translation>
    </message>
    <message>
        <source>Initial Node</source>
        <translation>Bắt đầu</translation>
    </message>
    <message>
        <source>The entry point of the program execution. Each diagram should have only one such block, it must not have incomming links and it must have only one outgoing link. The interpretation process starts from exactly this block.</source>
        <translation>Điểm khởi đầu của chương trình. Mỗi sơ đồ chỉ nên có một khối như vậy, không được có liên kết đi vào và chỉ được có một liên kết đi ra. Quá trình thông dịch bắt đầu chính xác từ khối này.</translation>
    </message>
    <message>
        <source>User Input</source>
        <translation>Nhập từ người dùng</translation>
    </message>
    <message>
        <source>Reads a value into variable from an input dialog.</source>
        <translation>Đọc một giá trị vào biến từ hộp thoại nhập liệu.</translation>
    </message>
    <message>
        <source>Default:</source>
        <translation>Mặc định:</translation>
    </message>
    <message>
        <source>Text:</source>
        <translation>Văn bản:</translation>
    </message>
    <message>
        <source>Join</source>
        <translation>Gộp nhiệm vụ</translation>
    </message>
    <message>
        <source>Joins a number of threads into one. &apos;Guard&apos; property of the single outgoing link must contain an identifier of one of threads being joined. The specified thread would wait until the rest of them finish execution, and then proceed in a normal way.</source>
        <translation>Gộp nhiều luồng thành một. Thuộc tính &apos;Điều kiện&apos; của liên kết đi ra duy nhất phải chứa định danh của một trong các luồng đang được gộp. Luồng được chỉ định sẽ chờ cho đến khi các luồng còn lại hoàn thành thực thi, sau đó tiếp tục theo cách thông thường.</translation>
    </message>
    <message>
        <source>Kill Thread</source>
        <translation>Kết thúc nhiệm vụ</translation>
    </message>
    <message>
        <source>Terminates execution of a specified thread.</source>
        <translation>Kết thúc việc thực thi một luồng đã chỉ định.</translation>
    </message>
    <message>
        <source>Thread:</source>
        <translation>Nhiệm vụ:</translation>
    </message>
    <message>
        <source>main</source>
        <translation>main</translation>
    </message>
    <message>
        <source>Thread</source>
        <translation>Nhiệm vụ</translation>
    </message>
    <message>
        <source>Loop</source>
        <translation>Vòng lặp</translation>
    </message>
    <message>
        <source>This block executes a sequence of blocks for a given number of times. The number of repetitions is specified by the &apos;Iterations&apos; parameter. This block must have two outgoing links. One of them must be marked with the &apos;body&apos; guard (that means that the property &apos;Guard&apos; of the link must be set to &apos;body&apos; value). Another outgoing link must be unmarked: the program execution will be proceeded through this link when it will go through our &apos;Loop&apos; block for the given number of times.</source>
        <translation>Khối này thực thi một dãy khối một số lần nhất định. Số lần lặp được xác định bởi tham số &apos;Số lần lặp&apos;. Khối này phải có hai liên kết đi ra. Một trong số đó phải được đánh dấu bằng điều kiện &apos;body&apos; (có nghĩa là thuộc tính &apos;Điều kiện&apos; của liên kết phải được đặt thành giá trị &apos;body&apos;). Liên kết đi ra còn lại phải không đánh dấu: chương trình sẽ tiếp tục thực thi qua liên kết này khi đã đi qua khối &apos;Vòng lặp&apos; đủ số lần quy định.</translation>
    </message>
    <message>
        <source>Iterations:</source>
        <translation>Số lần lặp:</translation>
    </message>
    <message>
        <source>10</source>
        <translation>10</translation>
    </message>
    <message>
        <source>Iterations</source>
        <translation>Số lần lặp</translation>
    </message>
    <message>
        <source>Marker Down</source>
        <translation>Hạ bút</translation>
    </message>
    <message>
        <source>Moves the marker of the 2D model robot down to the floor: the robot will draw its trace on the floor after that. If the marker of another color is already drawing at the moment it will be replaced.</source>
        <translation>Hạ bút vẽ của robot mô hình 2D xuống sàn: robot sẽ bắt đầu vẽ quỹ đạo của nó trên sàn. Nếu bút vẽ màu khác đang vẽ, nó sẽ bị thay thế.</translation>
    </message>
    <message>
        <source>Color:</source>
        <translation>Màu:</translation>
    </message>
    <message>
        <source>Color</source>
        <translation>Màu</translation>
    </message>
    <message>
        <source>Marker Up</source>
        <translation>Nhấc bút</translation>
    </message>
    <message>
        <source>Lifts the marker of the 2D model robot up: the robot stops drawing its trace on the floor after that.</source>
        <translation>Nhấc bút vẽ của robot mô hình 2D lên: robot sẽ ngừng vẽ quỹ đạo của nó trên sàn.</translation>
    </message>
    <message>
        <source>Pre-conditional Loop</source>
        <translation>Vòng lặp với điều kiện trước</translation>
    </message>
    <message>
        <source>This block executes a sequence of blocks while condition in &apos;Condition&apos; is true. This block must have two outgoing links. One of them must be marked with the &apos;body&apos; guard (that means that the property &apos;Guard&apos; of the link must be set to &apos;body&apos; value). Another outgoing link must be unmarked: the program execution will be proceeded through this link when condition becomes false.</source>
        <translation>Khối này thực thi một dãy khối trong khi điều kiện trong &apos;Điều kiện&apos; là đúng. Khối này phải có hai liên kết đi ra. Một trong số đó phải được đánh dấu bằng điều kiện &apos;body&apos; (có nghĩa là thuộc tính &apos;Điều kiện&apos; của liên kết phải được đặt thành giá trị &apos;body&apos;). Liên kết đi ra còn lại phải không đánh dấu: chương trình sẽ tiếp tục thực thi qua liên kết này khi điều kiện trở thành sai.</translation>
    </message>
    <message>
        <source>Print Text</source>
        <translation>In văn bản</translation>
    </message>
    <message>
        <source>Prints a given line in the specified coordinates on the robot`s screen. The value of &apos;Text&apos; property is interpreted as a plain text unless &apos;Evaluate&apos; property is set to true, then it will be interpreted as an expression (that may be useful for example when debugging variables values).</source>
        <translation>In một dòng văn bản đã cho tại tọa độ chỉ định trên màn hình robot. Giá trị thuộc tính &apos;Văn bản&apos; được hiểu là văn bản thuần túy trừ khi thuộc tính &apos;Đánh giá&apos; được đặt là đúng, khi đó nó sẽ được hiểu là một biểu thức (có thể hữu ích ví dụ khi gỡ lỗi giá trị biến).</translation>
    </message>
    <message>
        <source>X:</source>
        <translation>X:</translation>
    </message>
    <message>
        <source>Y:</source>
        <translation>Y:</translation>
    </message>
    <message>
        <source>Evaluate</source>
        <translation>Đánh giá</translation>
    </message>
    <message>
        <source>Enter some text here</source>
        <translation>Nhập văn bản tại đây</translation>
    </message>
    <message>
        <source>Text</source>
        <translation>Văn bản</translation>
    </message>
    <message>
        <source>1</source>
        <translation>1</translation>
    </message>
    <message>
        <source>X</source>
        <translation>X</translation>
    </message>
    <message>
        <source>Y</source>
        <translation>Y</translation>
    </message>
    <message>
        <source>Random Initialization</source>
        <translation>Khởi tạo ngẫu nhiên</translation>
    </message>
    <message>
        <source>Sets a variable value to a random value inside given interval.</source>
        <translation>Gán một giá trị ngẫu nhiên trong khoảng đã cho cho biến.</translation>
    </message>
    <message>
        <source>From:</source>
        <translation>Từ:</translation>
    </message>
    <message>
        <source>To:</source>
        <translation>Đến:</translation>
    </message>
    <message>
        <source>0</source>
        <translation>0</translation>
    </message>
    <message>
        <source>From</source>
        <translation>Từ</translation>
    </message>
    <message>
        <source>To</source>
        <translation>Đến</translation>
    </message>
    <message>
        <source>Receive Message From Thread</source>
        <translation>Nhận tin nhắn từ luồng</translation>
    </message>
    <message>
        <source>Receive a message sent to a thread from which this block is called.</source>
        <translation>Nhận tin nhắn được gửi đến luồng mà khối này được gọi từ đó.</translation>
    </message>
    <message>
        <source>Synchronized:</source>
        <translation>Đồng bộ hóa:</translation>
    </message>
    <message>
        <source>Synchronized</source>
        <translation>Đồng bộ hóa</translation>
    </message>
    <message>
        <source>RobotsDiagramGroup</source>
        <translation>Biểu đồ hành vi robot</translation>
    </message>
    <message>
        <source>Robot`s Behaviour Diagram</source>
        <translation>Biểu đồ hành vi robot</translation>
    </message>
    <message>
        <source>Send Message To Thread</source>
        <translation>Gửi tin nhắn đến luồng</translation>
    </message>
    <message>
        <source>Sends a message to a specified thread.</source>
        <translation>Gửi một tin nhắn đến luồng đã chỉ định.</translation>
    </message>
    <message>
        <source>Message:</source>
        <translation>Tin nhắn:</translation>
    </message>
    <message>
        <source>Subprogram</source>
        <translation>Chương trình con</translation>
    </message>
    <message>
        <source>Subprogram call. Subprograms are used for splitting repetitive program parts into a separate diagram and then calling it from main diagram or other subprograms. When this block is added into a diagram it will be suggested to enter subprogram name. The double click on subprogram call block may open the corresponding subprogram diagram. Moreover user palette will appear containing existing subrpograms, they can be dragged into a diagram like the usual blocks.</source>
        <translation>Gọi chương trình con. Các chương trình con được dùng để tách các phần chương trình lặp lại thành một biểu đồ riêng, sau đó gọi từ biểu đồ chính hoặc các chương trình con khác. Khi khối này được thêm vào biểu đồ, người dùng sẽ được yêu cầu nhập tên chương trình con. Nhấp đúp vào khối gọi chương trình con có thể mở biểu đồ chương trình con tương ứng. Ngoài ra, bảng chọn người dùng sẽ xuất hiện chứa các chương trình con hiện có, có thể kéo thả chúng vào biểu đồ như các khối thông thường.</translation>
    </message>
    <message>
        <source>Subprogram Diagram</source>
        <translation>Biểu đồ chương trình con</translation>
    </message>
    <message>
        <source>SubprogramDiagramGroup</source>
        <translation>Chương trình con</translation>
    </message>
    <message>
        <source>Switch</source>
        <translation>Lựa chọn</translation>
    </message>
    <message>
        <source>Selects the program execution branch in correspondence with some expression value. The value of the expression written in &apos;Expression&apos; property is compared to the values on the outgoing links. If equal value is found then execution will be proceeded by that branch. Else branch without a marker will be selected.</source>
        <translation>Chọn nhánh thực thi chương trình tương ứng với giá trị của một biểu thức. Giá trị của biểu thức trong thuộc tính &apos;Biểu thức&apos; sẽ được so sánh với các giá trị trên các liên kết đi ra. Nếu tìm thấy giá trị bằng nhau, chương trình sẽ tiếp tục theo nhánh đó. Nếu không, nhánh không có nhãn sẽ được chọn.</translation>
    </message>
    <message>
        <source>Timer</source>
        <translation>Bộ đếm thời gian</translation>
    </message>
    <message>
        <source>Waits for a given time in milliseconds.</source>
        <translation>Chờ trong khoảng thời gian đã cho tính bằng mili giây.</translation>
    </message>
    <message>
        <source>Delay:</source>
        <translation>Độ trễ:</translation>
    </message>
    <message>
        <source>ms</source>
        <translation>ms</translation>
    </message>
    <message>
        <source>1000</source>
        <translation>1000</translation>
    </message>
    <message>
        <source>Delay (ms)</source>
        <translation>Độ trễ (ms)</translation>
    </message>
    <message>
        <source>Variable Initialization</source>
        <translation>Khởi tạo biến</translation>
    </message>
    <message>
        <source>Assigns a given value to a given variable.</source>
        <translation>Gán một giá trị đã cho cho một biến đã cho.</translation>
    </message>
    <message>
        <source>Value:</source>
        <translation>Giá trị:</translation>
    </message>
    <message>
        <source>Value</source>
        <translation>Giá trị</translation>
    </message>
    <message>
        <source>Algorithms</source>
        <translation>Thuật toán</translation>
    </message>
    <message>
        <source>Actions</source>
        <translation>Hành động</translation>
    </message>
    <message>
        <source>Drawing</source>
        <translation>Vẽ</translation>
    </message>
</context>
<context>
    <name>QObject::QObject</name>
    <message>
        <source>Expression</source>
        <translation>Biểu thức</translation>
    </message>
    <message>
        <source>Default</source>
        <translation>Mặc định</translation>
    </message>
    <message>
        <source>Text</source>
        <translation>Văn bản</translation>
    </message>
    <message>
        <source>Variable</source>
        <translation>Biến</translation>
    </message>
    <message>
        <source>Devices configuration</source>
        <translation>Cấu hình thiết bị</translation>
    </message>
    <message>
        <source>Message</source>
        <translation>Tin nhắn</translation>
    </message>
    <message>
        <source>Thread</source>
        <translation>Nhiệm vụ</translation>
    </message>
</context>
<context>
    <name>RobotsMetamodelPlugin</name>
    <message>
        <source>norm</source>
        <translation>chuẩn</translation>
    </message>
    <message>
        <source>x-axis</source>
        <translation>trục x</translation>
    </message>
    <message>
        <source>y-axis</source>
        <translation>trục y</translation>
    </message>
    <message>
        <source>z-axis</source>
        <translation>trục z</translation>
    </message>
    <message>
        <source>Composite</source>
        <translation>Hợp thành</translation>
    </message>
    <message>
        <source>None</source>
        <translation>Không có</translation>
    </message>
    <message>
        <source>Shared</source>
        <translation>Chung</translation>
    </message>
    <message>
        <source>brake</source>
        <translation>phanh</translation>
    </message>
    <message>
        <source>float</source>
        <translation>trôi</translation>
    </message>
    <message>
        <source>Concurrent</source>
        <translation>Đồng thời</translation>
    </message>
    <message>
        <source>Guarded</source>
        <translation>Được bảo vệ</translation>
    </message>
    <message>
        <source>Sequential</source>
        <translation>Tuần tự</translation>
    </message>
    <message>
        <source>black</source>
        <translation>đen</translation>
    </message>
    <message>
        <source>blue</source>
        <translation>xanh dương</translation>
    </message>
    <message>
        <source>green</source>
        <translation>xanh lá</translation>
    </message>
    <message>
        <source>red</source>
        <translation>đỏ</translation>
    </message>
    <message>
        <source>white</source>
        <translation>trắng</translation>
    </message>
    <message>
        <source>yellow</source>
        <translation>vàng</translation>
    </message>
    <message>
        <source>greater</source>
        <translation>lớn hơn</translation>
    </message>
    <message>
        <source>less</source>
        <translation>nhỏ hơn</translation>
    </message>
    <message>
        <source>not greater</source>
        <translation>không lớn hơn</translation>
    </message>
    <message>
        <source>not less</source>
        <translation>không nhỏ hơn</translation>
    </message>
    <message>
        <source>false</source>
        <translation>sai</translation>
    </message>
    <message>
        <source>body</source>
        <translation>thân vòng lặp</translation>
    </message>
    <message>
        <source>true</source>
        <translation>đúng</translation>
    </message>
    <message>
        <source>In</source>
        <translation>Đầu vào</translation>
    </message>
    <message>
        <source>Inout</source>
        <translation>Đầu vào - đầu ra</translation>
    </message>
    <message>
        <source>Out</source>
        <translation>Đầu ra</translation>
    </message>
    <message>
        <source>Return</source>
        <translation>Trả về</translation>
    </message>
    <message>
        <source>Package</source>
        <translation>Gói</translation>
    </message>
    <message>
        <source>Private</source>
        <translation>Riêng tư</translation>
    </message>
    <message>
        <source>Protected</source>
        <translation>Được bảo vệ</translation>
    </message>
    <message>
        <source>Public</source>
        <translation>Công khai</translation>
    </message>
</context>
</TS>
