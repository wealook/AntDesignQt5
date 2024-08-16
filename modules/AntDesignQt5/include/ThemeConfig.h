#pragma once

#include <string>

namespace wl {
    class ThemeConfig {

    public:
        static const ThemeConfig &Instance() {
            static ThemeConfig _instance = ThemeConfig();
            return _instance;
        }


// SeedToken
        double borderRadius = 6;//	基础组件的圆角大小，例如按钮、输入框、卡片等
        std::string colorBgBase = "#fff";//	用于派生背景色梯度的基础变量，v5 中我们添加了一层背景色的派生算法可以产出梯度明确的背景色的梯度变量。但请不要在代码中直接使用该 Seed Token ！
        std::string colorError = "#ff4d4f";//	用于表示操作失败的 Token 序列，如失败按钮、错误状态提示（Result）组件等。
        std::string colorInfo = "#1677ff";//	用于表示操作信息的 Token 序列，如 Alert 、Tag、 Progress 等组件都有用到该组梯度变量。
        std::string colorLink = "#1677ff";//	控制超链接的颜色。
        std::string colorPrimary = "#1677ff";//	品牌色是体现产品特性和传播理念最直观的视觉元素之一。在你完成品牌主色的选取之后，我们会自动帮你生成一套完整的色板，并赋予它们有效的设计语义
        std::string colorSuccess = "#52c41a";//	用于表示操作成功的 Token 序列，如 Result、Progress 等组件会使用该组梯度变量。
        std::string colorTextBase = "#000";//	用于派生文本色梯度的基础变量，v5 中我们添加了一层文本色的派生算法可以产出梯度明确的文本色的梯度变量。但请不要在代码中直接使用该 Seed Token ！
        std::string colorWarning = "#faad14";//	用于表示操作警告的 Token 序列，如 Notification、 Alert等警告类组件或 Input 输入类等组件会使用该组梯度变量。
        double controlHeight = 32;//	Ant Design 中按钮和输入框等基础控件的高度
        std::string fontFamily = "-apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, 'Noto Sans', sans-serif, 'Apple Color Emoji', 'Segoe UI Emoji', 'Segoe UI Symbol', 'Noto Color Emoji'";//	Ant Design 的字体家族中优先使用系统默认的界面字体，同时提供了一套利于屏显的备用字体库，来维护在不同平台以及浏览器的显示下，字体始终保持良好的易读性和可读性，体现了友好、稳定和专业的特性。
        std::string fontFamilyCode = "'SFMono-Regular', Consolas, 'Liberation Mono', Menlo, Courier, monospace";//	代码字体，用于 Typography 内的 code、pre 和 kbd 类型的元素
        double fontSize = 14;//	设计系统中使用最广泛的字体大小，文本梯度也将基于该字号进行派生。
        std::string lineType = "solid";//	用于控制组件边框、分割线等的样式，默认是实线
        double lineWidth = 1;//	用于控制组件边框、分割线等的宽度
        bool motion = true;//	用于配置动画效果，为 `false` 时则关闭动画
        double motionBase = 0;//
        std::string motionEaseInBack = "cubic-bezier(0.71, -0.46, 0.88, 0.6)";//	预设动效曲率
        std::string motionEaseInOut = "cubic-bezier(0.645, 0.045, 0.355, 1)";//	预设动效曲率
        std::string motionEaseInOutCirc = "cubic-bezier(0.78, 0.14, 0.15, 0.86)";//	预设动效曲率
        std::string motionEaseInQuint = "cubic-bezier(0.755, 0.05, 0.855, 0.06)";//	预设动效曲率
        std::string motionEaseOut = "cubic-bezier(0.215, 0.61, 0.355, 1)";//	预设动效曲率
        std::string motionEaseOutBack = "cubic-bezier(0.12, 0.4, 0.29, 1.46)";//	预设动效曲率
        std::string motionEaseOutCirc = "cubic-bezier(0.08, 0.82, 0.17, 1)";//	预设动效曲率
        std::string motionEaseOutQuint = "cubic-bezier(0.23, 1, 0.32, 1)";//	预设动效曲率
        double motionUnit = 0.1;//	用于控制动画时长的变化单位
        double opacityImage = 1;//
        double sizePopupArrow = 16;//	组件箭头的尺寸
        double sizeStep = 4;//	用于控制组件尺寸的基础步长，尺寸步长结合尺寸变化单位，就可以派生各种尺寸梯度。通过调整步长即可得到不同的布局模式，例如 V5 紧凑模式下的尺寸步长为 2
        double sizeUnit = 4;//	用于控制组件尺寸的变化单位，在 Ant Design 中我们的基础单位为 4 ，便于更加细致地控制尺寸梯度
        bool wireframe = false;//	用于将组件的视觉效果变为线框化，如果需要使用 V4 的效果，需要开启配置项
        double zIndexBase = 0;//	所有组件的基础 Z 轴值，用于一些悬浮类的组件的可以基于该值 Z 轴控制层级，例如 BackTop、 Affix 等

        //  MapToken                继承所有 SeedToken 的属性

        double borderRadiusLG = 8;    //	LG号圆角，用于组件中的一些大圆角，如 Card、Modal 等一些组件样式。
        double borderRadiusOuter = 4;    //	外部圆角
        double borderRadiusSM = 4;    //	SM号圆角，用于组件小尺寸下的圆角，如 Button、Input、Select 等输入类控件在 small size 下的圆角
        double borderRadiusXS = 2;    //	XS号圆角，用于组件中的一些小圆角，如 Segmented 、Arrow 等一些内部圆角的组件样式中。
        std::string colorBgBlur = "transparent";    //	控制毛玻璃容器的背景色，通常为透明色。
        std::string colorBgContainer = "#ffffff";    //	组件的容器背景色，例如：默认按钮、输入框等。务必不要将其与 `colorBgElevated` 混淆。
        std::string colorBgElevated = "#ffffff";    //	浮层容器背景色，在暗色模式下该 token 的色值会比 `colorBgContainer` 要亮一些。例如：模态框、弹出框、菜单等。
        std::string colorBgLayout = "#f5f5f5";    //	该色用于页面整体布局的背景色，只有需要在页面中处于 B1 的视觉层级时才会使用该 token，其他用法都是错误的
        std::string colorBgMask = "rgba(0, 0, 0, 0.45)";    //	浮层的背景蒙层颜色，用于遮罩浮层下面的内容，Modal、Drawer 等组件的蒙层使用的是该 token
        std::string colorBgSpotlight = "rgba(0, 0, 0, 0.85)";    //	该色用于引起用户强烈关注注意的背景色，目前只用在 Tooltip 的背景色上。
        std::string colorBorder = "#d9d9d9";    //	默认使用的边框颜色, 用于分割不同的元素，例如：表单的分割线、卡片的分割线等。
        std::string colorBorderSecondary = "#f0f0f0";    //	比默认使用的边框色要浅一级，此颜色和 colorSplit 的颜色一致。使用的是实色。
        std::string colorBgSecondary = "#f0f0f0";    //	比默认使用的边框色要浅一级，此颜色和 colorSplit 的颜色一致。使用的是实色。
        std::string colorErrorActive = "#d9363e";    //	错误色的深色激活态
        std::string colorErrorBg = "#fff2f0";    //	错误色的浅色背景颜色
        std::string colorErrorBgActive = "#ffccc7";    //	错误色的浅色背景色激活态
        std::string colorErrorBgHover = "#fff1f0";    //	错误色的浅色背景色悬浮态
        std::string colorErrorBorder = "#ffccc7";    //	错误色的描边色
        std::string colorErrorBorderHover = "#ffa39e";    //	错误色的描边色悬浮态
        std::string colorErrorHover = "#ff7875";    //	错误色的深色悬浮态
        std::string colorErrorText = "#ff4d4f";    //	错误色的文本默认态
        std::string colorErrorTextActive = "#d9363e";    //	错误色的文本激活态
        std::string colorErrorTextHover = "#ff7875";    //	错误色的文本悬浮态
        std::string colorFill = "rgba(0, 0, 0, 0.15)";    //	最深的填充色，用于拉开与二、三级填充色的区分度，目前只用在 Slider 的 hover 效果。
        std::string colorFillQuaternary = "rgba(0, 0, 0, 0.02)";    //	最弱一级的填充色，适用于不易引起注意的色块，例如斑马纹、区分边界的色块等。
        std::string colorFillSecondary = "rgba(0, 0, 0, 0.06)";    //	二级填充色可以较为明显地勾勒出元素形体，如 Rate、Skeleton 等。也可以作为三级填充色的 Hover 状态，如 Table 等。
        std::string colorFillTertiary = "rgba(0, 0, 0, 0.04)";    //	三级填充色用于勾勒出元素形体的场景，如 Slider、Segmented 等。如无强调需求的情况下，建议使用三级填色作为默认填色。
        std::string colorInfoActive = "#0958d9";    //	信息色的深色激活态。
        std::string colorInfoBg = "#e6f4ff";    //	信息色的浅色背景颜色。
        std::string colorInfoBgHover = "#bae0ff";    //	信息色的浅色背景色悬浮态。
        std::string colorInfoBorder = "#91caff";    //	信息色的描边色。
        std::string colorInfoBorderHover = "#69b1ff";    //	信息色的描边色悬浮态。
        std::string colorInfoHover = "#69b1ff";    //	信息色的深色悬浮态。
        std::string colorInfoText = "#1677ff";    //	信息色的文本默认态。
        std::string colorInfoTextActive = "#0958d9";    //	信息色的文本激活态。
        std::string colorInfoTextHover = "#4096ff";    //	信息色的文本悬浮态。
        std::string colorLinkActive = "#0958d9";    //	控制超链接被点击时的颜色。
        std::string colorLinkHover = "#69b1ff";    //	控制超链接悬浮时的颜色。
        std::string colorPrimaryActive = "#0958d9";    //	主色梯度下的深色激活态。
        std::string colorPrimaryBg = "#e6f4ff";    //	主色浅色背景颜色，一般用于视觉层级较弱的选中状态。
        std::string colorPrimaryBgHover = "#bae0ff";    //	与主色浅色背景颜色相对应的悬浮态颜色。
        std::string colorPrimaryBorder = "#91caff";    //	主色梯度下的描边用色，用在 Slider 等组件的描边上。
        std::string colorPrimaryBorderHover = "#69b1ff";    //	主色梯度下的描边用色的悬浮态，Slider 、Button 等组件的描边 Hover 时会使用。
        std::string colorPrimaryHover = "#4096ff";    //	主色梯度下的悬浮态。
        std::string colorPrimaryText = "#1677ff";    //	主色梯度下的文本颜色。
        std::string colorPrimaryTextActive = "#0958d9";    //	主色梯度下的文本激活态。
        std::string colorPrimaryTextHover = "#4096ff";    //	主色梯度下的文本悬浮态。
        std::string colorSuccessActive = "#389e0d";    //	成功色的深色激活态
        std::string colorSuccessBg = "#f6ffed";    //	成功色的浅色背景颜色，用于 Tag 和 Alert 的成功态背景色
        std::string colorSuccessBgHover = "#d9f7be";    //	成功色浅色背景颜色，一般用于视觉层级较弱的选中状态，不过 antd 目前没有使用到该 token
        std::string colorSuccessBorder = "#b7eb8f";    //	成功色的描边色，用于 Tag 和 Alert 的成功态描边色
        std::string colorSuccessBorderHover = "#95de64";    //	成功色的描边色悬浮态
        std::string colorSuccessHover = "#95de64";    //	成功色的深色悬浮态
        std::string colorSuccessText = "#52c41a";    //	成功色的文本默认态
        std::string colorSuccessTextActive = "#389e0d";    //	成功色的文本激活态
        std::string colorSuccessTextHover = "#73d13d";    //	成功色的文本悬浮态
        std::string colorText = "rgba(0, 0, 0, 0.88)";    //	最深的文本色。为了符合W3C标准，默认的文本颜色使用了该色，同时这个颜色也是最深的中性色。
        std::string colorTextQuaternary = "rgba(0, 0, 0, 0.25)";    //	第四级文本色是最浅的文本色，例如表单的输入提示文本、禁用色文本等。
        std::string colorTextSecondary = "rgba(0, 0, 0, 0.65)";    //	作为第二梯度的文本色，一般用在不那么需要强化文本颜色的场景，例如 Label 文本、Menu 的文本选中态等场景。
        std::string colorTextTertiary = "rgba(0, 0, 0, 0.45)";    //	第三级文本色一般用于描述性文本，例如表单的中的补充说明文本、列表的描述性文本等场景。
        std::string colorWarningActive = "#d48806";    //	警戒色的深色激活态
        std::string colorWarningBg = "#fffbe6";    //	警戒色的浅色背景颜色
        std::string colorWarningBgHover = "#fff1b8";    //	警戒色的浅色背景色悬浮态
        std::string colorWarningBorder = "#ffe58f";    //	警戒色的描边色
        std::string colorWarningBorderHover = "#ffd666";    //	警戒色的描边色悬浮态
        std::string colorWarningHover = "#ffd666";    //	警戒色的深色悬浮态
        std::string colorWarningText = "#faad14";    //	警戒色的文本默认态
        std::string colorWarningTextActive = "#d48806";    //	警戒色的文本激活态
        std::string colorWarningTextHover = "#ffc53d";    //	警戒色的文本悬浮态
        std::string colorWhite = "#fff";    //	不随主题变化的纯白色
        double controlHeightLG = 40;    //	较高的组件高度
        double controlHeightSM = 24;    //	较小的组件高度
        double controlHeightXS = 16;    //	更小的组件高度
        double fontSizeHeading1 = 38;    //	H1 标签所使用的字号
        double fontSizeHeading2 = 30;    //	h2 标签所使用的字号
        double fontSizeHeading3 = 24;    //	h3 标签使用的字号
        double fontSizeHeading4 = 20;    //	h4 标签使用的字号
        double fontSizeHeading5 = 16;    //	h5 标签使用的字号
        double fontSizeLG = 16;    //	大号字体大小
        double fontSizeSM = 12;    //	小号字体大小
        double fontSizeXL = 20;    //	超大号字体大小
        double lineHeight = 1.571428571;    //	文本行高
        double lineHeightHeading1 = 1.210526316;    //	H1 标签所使用的行高
        double lineHeightHeading2 = 1.266666667;    //	h2 标签所使用的行高
        double lineHeightHeading3 = 1.333333333;    //	h3 标签所使用的行高
        double lineHeightHeading4 = 1.4;    //	h4 标签所使用的行高
        double lineHeightHeading5 = 1.5;    //	h5 标签所使用的行高
        double lineHeightLG = 1.5;    //	大型文本行高
        double lineHeightSM = 1.666666667;    //	小型文本行高
        double lineWidthBold = 2;    //	描边类组件的默认线宽，如 Button、Input、Select 等输入类控件。
        std::string motionDurationFast = "0.1s";    //	动效播放速度，快速。用于小型元素动画交互
        std::string motionDurationMid = "0.2s";    //	动效播放速度，中速。用于中型元素动画交互
        std::string motionDurationSlow = "0.3s";    //	动效播放速度，慢速。用于大型元素如面板动画交互
        double size = 16;    //	默认尺寸
        double sizeLG = 24;    //
        double sizeMD = 20;    //
        double sizeMS = 16;    //
        double sizeSM = 12;    //
        double sizeXL = 32;    //
        double sizeXS = 8;    //
        double sizeXXL = 48;    //
        double sizeXXS = 4;    //
        std::string colorDanger = "rgb(255,77,79)";
        std::string colorDangerHover = "rgb(255,120,117)";
        std::string colorDisabled = "rgb(245,245,245)";
        std::string colorDisabledText = "rgb(217,217,217)";
        std::string colorDisabledBorder = "rgb(217,217,217)";
        std::string colorDisabledDepth = "rgb(191,191,191)";

        std::string colorBgTextMark = "rgb(255, 229, 143 )";    //	第三级文本色一般用于描述性文本，例如表单的中的补充说明文本、列表的描述性文本等场景。
        std::string colorBgTextCode = "rgba(150, 150, 150 ,0.1)";    //	第三级文本色一般用于描述性文本，例如表单的中的补充说明文本、列表的描述性文本等场景。
        std::string colorBgTextKeyword = "rgba(150, 150, 150 ,0.1)";    //	第三级文本色一般用于描述性文本，例如表单的中的补充说明文本、列表的描述性文本等场景。


        //AliasToken                 继承所有 SeedToken 和 MapToken 的属性
        std::string boxShadow = "0 6px 16px 0 rgba(0, 0, 0, 0.08), 0 3px 6px -4px rgba(0, 0, 0, 0.12), 0 9px 28px 8px rgba(0, 0, 0, 0.05)";//	控制元素阴影样式。
        std::string boxShadowSecondary = "0 6px 16px 0 rgba(0, 0, 0, 0.08), 0 3px 6px -4px rgba(0, 0, 0, 0.12), 0 9px 28px 8px rgba(0, 0, 0, 0.05)";//	控制元素二级阴影样式。
        std::string boxShadowTertiary = "0 1px 2px 0 rgba(0, 0, 0, 0.03), 0 1px 6px -1px rgba(0, 0, 0, 0.02), 0 2px 4px 0 rgba(0, 0, 0, 0.02)";//	控制元素三级盒子阴影样式。
        std::string colorBgContainerDisabled = "rgba(0, 0, 0, 0.04)";//	控制容器在禁用状态下的背景色。
        std::string colorBgTextActive = "rgba(0, 0, 0, 0.15)";//	控制文本在激活状态下的背景色。
        std::string colorBgTextHover = "rgba(0, 0, 0, 0.06)";//	控制文本在悬停状态下的背景色。
        std::string colorBorderBg = "#ffffff";//	控制元素背景边框的颜色。
        std::string colorErrorOutline = "rgba(255, 38, 5, 0.06)";//	控制输入组件错误状态下的外轮廓线颜色。
        std::string colorFillAlter = "rgba(0, 0, 0, 0.02)";//	控制元素替代背景色。
        std::string colorFillContent = "rgba(0, 0, 0, 0.06)";//	控制内容区域的背景色。
        std::string colorFillContentHover = "rgba(0, 0, 0, 0.15)";//	控制内容区域背景色在鼠标悬停时的样式。
        std::string colorHighlight = "#ff4d4f";//	控制页面元素高亮时的颜色。
        std::string colorIcon = "rgba(0, 0, 0, 0.45)";//	控制弱操作图标的颜色，例如 allowClear 或 Alert 关闭按钮。 *
        std::string colorIconHover = "rgba(0, 0, 0, 0.88)";//	控制弱操作图标在悬浮状态下的颜色，例如 allowClear 或 Alert 关闭按钮。
        std::string colorSplit = "rgba(5, 5, 5, 0.06)";//	用于作为分割线的颜色，此颜色和 colorBorderSecondary 的颜色一致，但是用的是透明色。
        std::string colorTextDescription = "rgba(0, 0, 0, 0.45)";//	控制文本描述字体颜色。
//        std::string colorTextDisabled = "rgba(0, 0, 0, 0.25)";//	控制禁用状态下的字体颜色。
        std::string colorTextDisabled = "rgb(140, 140, 140)";//	控制禁用状态下的字体颜色。
        std::string colorTextHeading = "rgba(0, 0, 0, 0.88)";//	控制标题字体颜色。
        std::string colorTextLabel = "rgba(0, 0, 0, 0.65)";//	控制文本标签字体颜色。
        std::string colorTextLightSolid = "#fff";//	控制带背景色的文本，例如 Primary Button 组件中的文本高亮颜色。
        std::string colorTextPlaceholder = "rgba(0, 0, 0, 0.25)";//	控制占位文本的颜色。
        std::string colorWarningOutline = "rgba(255, 215, 5, 0.1)";//	控制输入组件警告状态下的外轮廓线颜色。
        double controlInteractiveSize = 16;//	控制组件的交互大小。
        std::string controlItemBgActive = "#e6f4ff";//	控制组件项在激活状态下的背景颜色。
        std::string controlItemBgActiveDisabled = "rgba(0, 0, 0, 0.15)";//	控制组件项在禁用状态下的激活背景颜色。
        std::string controlItemBgActiveHover = "#bae0ff";//	控制组件项在鼠标悬浮且激活状态下的背景颜色。
        std::string controlItemBgHover = "rgba(0, 0, 0, 0.04)";//	控制组件项在鼠标悬浮时的背景颜色。
        std::string controlOutline = "rgba(5, 145, 255, 0.1)";//	控制输入组件的外轮廓线颜色。
        double controlOutlineWidth = 2;//	控制输入组件的外轮廓线宽度。
        double controlPaddingHorizontal = 12;//	控制元素水平内间距。
        double controlPaddingHorizontalSM = 8;//	控制元素中小尺寸水平内间距。
        double fontSizeIcon = 12;//	控制选择器、级联选择器等中的操作图标字体大小。正常情况下与 fontSizeSM 相同。
        double fontWeightStrong = 600;//	控制标题类组件（如 h1、h2、h3）或选中项的字体粗细。
        double lineWidthFocus = 4;//	控制线条的宽度，当组件处于聚焦态时。
        /*  /        undefined |
          TextDecoration<std::string | double> linkDecoration = none;//	控制链接文本的装饰样式。
          /        undefined |
          TextDecoration<std::string | double> linkFocusDecoration = none;//	控制链接聚焦时文本的装饰样式。
          /        undefined |
          TextDecoration<std::string | double> linkHoverDecoration = none;//	控制链接鼠标悬浮时文本的装饰样式。*/
        double margin = 16;//	控制元素外边距，中等尺寸。
        double marginLG = 24;//	控制元素外边距，大尺寸。
        double marginMD = 20;//	控制元素外边距，中大尺寸。
        double marginSM = 12;//	控制元素外边距，中小尺寸。
        double marginXL = 32;//	控制元素外边距，超大尺寸。
        double marginXS = 8;//	控制元素外边距，小尺寸。
        double marginXXL = 48;//	控制元素外边距，最大尺寸。
        double marginXXS = 4;//	控制元素外边距，最小尺寸。
        double opacityLoading = 0.65;//	控制加载状态的透明度。
        double padding = 16;//	控制元素的内间距。
        double paddingContentHorizontal = 16;//	控制内容元素水平内间距。
        double paddingContentHorizontalLG = 24;//	控制内容元素水平内间距，适用于大屏幕设备。
        double paddingContentHorizontalSM = 16;//	控制内容元素水平内间距，适用于小屏幕设备。
        double paddingContentVertical = 12;//	控制内容元素垂直内间距。
        double paddingContentVerticalLG = 16;//	控制内容元素垂直内间距，适用于大屏幕设备。
        double paddingContentVerticalSM = 8;//	控制内容元素垂直内间距，适用于小屏幕设备。
        double paddingLG = 24;//	控制元素的大内间距。
        double paddingMD = 20;//	控制元素的中等内间距。
        double paddingSM = 12;//	控制元素的小内间距。
        double paddingXL = 32;//	控制元素的特大内间距。
        double paddingXS = 8;//	控制元素的特小内间距。
        double paddingXXS = 4;//	控制元素的极小内间距。
        double screenLG = 992;//	控制大屏幕的屏幕宽度。
        double screenLGMax = 1199;//	控制大屏幕的最大宽度。
        double screenLGMin = 992;//	控制大屏幕的最小宽度。
        double screenMD = 768;//	控制中等屏幕的屏幕宽度。
        double screenMDMax = 991;//	控制中等屏幕的最大宽度。
        double screenMDMin = 768;//	控制中等屏幕的最小宽度。
        double screenSM = 576;//	控制小屏幕的屏幕宽度。
        double screenSMMax = 767;//	控制小屏幕的最大宽度。
        double screenSMMin = 576;//	控制小屏幕的最小宽度。
        double screenXL = 1200;//	控制超大屏幕的屏幕宽度。
        double screenXLMax = 1599;//	控制超大屏幕的最大宽度。
        double screenXLMin = 1200;//	控制超大屏幕的最小宽度。
        double screenXS = 480;//	控制超小屏幕的屏幕宽度。
        double screenXSMax = 575;//	控制超小屏幕的最大宽度。
        double screenXSMin = 480;//	控制超小屏幕的最小宽度。
        double screenXXL = 1600;//	控制超超大屏幕的屏幕宽度。
        double screenXXLMin = 1600;//	控制超超大屏幕的最小宽度。



        std::string verticalScrollBar = R"(
            QScrollBar {
                    width: 8px;
                    background-color: #f0f0f0;
                    border: none;
            }
            QScrollBar::handle {
                    background-color: #c8c8c8;
                    border-radius: 4px;
            }
            QScrollBar::handle:hover {
                    background-color: #c8c8c8;
                    color:rgba(0,0,0,0.5);
                    height:50%;
            }
            QScrollBar::corner {
                    background: transparent;
            }
        )";
    protected:
        ThemeConfig() {

        }
    };


    class InputConfig : public ThemeConfig {
    public:

        static InputConfig Instance() {
            static InputConfig _instance = InputConfig();
            return _instance;
        }

        std::string activeBg = "#ffffff";//输入框激活状态时背景颜色
        std::string activeBorderColor = "#1677ff";//激活态边框色
        std::string activeShadow = "0 0 0 2px rgba(5, 145, 255, 0.1)";//激活态阴影
        std::string addonBg = "rgba(0, 0, 0, 0.02)";//前/后置标签背景色
        std::string errorActiveShadow = "0 0 0 2px rgba(255, 38, 5, 0.06)";//错误状态时激活态阴影
        std::string hoverBg = "#ffffff";//输入框hover状态时背景颜色
        std::string hoverBorderColor = "#4096ff";//悬浮态边框色
        int inputFontSize = 16; //字体大小
        int inputFontSizeLG = 22;//大号字体大小
        int inputFontSizeSM = 14;//小号字体大小
        int paddingBlock = 4;//输入框纵向内边距
        int paddingBlockLG = 7;//大号输入框纵向内边距
        int paddingBlockSM = 0;//小号输入框纵向内边距
        int paddingInline = 11;//输入框横向内边距
        int paddingInlineLG = 11;//大号输入框横向内边距
        int paddingInlineSM = 7;//小号输入框横向内边距
        std::string warningActiveShadow = "0 0 0 2px rgba(255, 215, 5, 0.1)";//警告状态时激活态阴影

        std::string colorInputFilledBG = "rgb(245,245,245)";//输入框 filled 背景色
        std::string colorInputFilledHoverBG = "rgb(240,240,240)";//输入框 filled  hover 背景色

    private:
        InputConfig() {
        }
    };

}

