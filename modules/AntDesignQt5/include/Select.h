#pragma  once

#include <QWidget>
#include "AWidget.h"
#include "SelectAttr.h"
#include <QListWidget>
#include <QScrollArea>
#include "HWidget.h"
#include "Text.h"
#include "Input.h"
#include "Flex.h"
#include "Tag.h"

namespace wl {


    class SelectActionOption : public SelectAttrOption {
    public:

        explicit SelectActionOption() = default;

        explicit SelectActionOption(const SelectAttrOption &option) : SelectAttrOption(option) {

        }

        // 当前编辑框正在编辑的一个选项
        bool isEditing = false;
        // 编辑框编辑完成的一个临时的选项
        bool isTmp = false;
        int sort = 0;
        bool isHide = false;

    };

    using SelectActionOptions = std::vector<SelectActionOption>;


    class SelectArea : public QScrollArea, public AWidget {
    Q_OBJECT
    public:

        explicit SelectArea(QWidget *parent = nullptr);

        void mousePressEvent(QMouseEvent *event) override;

        void mouseReleaseEvent(QMouseEvent *event) override;


        bool event(QEvent *) override;

        void renderOptions(const SelectActionOptions &options, bool update = false);

        void updateRenderOptions(const SelectActionOptions &options);

    protected slots:

        void onSelectItemClicked();

    signals:

        void selectItemClicked(const QString &val);

        void areaClicked();

        void blankSpaceClicked(QPoint);

    };

    class SelectWidget : public HWidget {
    Q_OBJECT

    public:
        explicit SelectWidget(QWidget *parent = nullptr);

        bool event(QEvent *) override;

        void renderOptions(const SelectActionOptions &options);

        void updateRenderOptions(const SelectActionOptions &options);

        void resizeEvent(QResizeEvent *event) override;


        std::function<bool(QPoint)> shouldHide = nullptr;

//        void closeEvent(QCloseEvent *event) override;

    private:
        SelectArea *selectArea_;

        bool shouldClose_ = true;
    signals:

        void selectItemClicked(const QString &val);

        void blankSpaceClicked(QPoint);
    };

    class Select : public HWidget {
    Q_OBJECT

    public:

        explicit Select(QWidget *parent = nullptr);


        void init();
//        void showEvent(QShowEvent *event) override;

//    void paintEvent();

//        [[nodiscard]] const SelectAttr &getAttr() const;

//        void setAttr(const SelectAttr &selectAttr);



        void mousePressEvent(QMouseEvent *event) override;


        void paintEvent(QPaintEvent *event) override;

        void updateAttr();

        void resizeEvent(QResizeEvent *event) override;

    private:
        void deleteSelected(const QString &val);

        void updateSelectWidgetPos();

    signals:

        void onDeselect(QString val);

        void onSelect(QString val);

    public slots:

        void onSelectItemClicked(const QString &);


    private:
        Text *text_ = nullptr;
        WLQLineEdit *input_ = nullptr;
        Flex *tags_ = nullptr;
        std::vector<Tag *> tagList_;
        HWidget *rightIcon_ = nullptr;
//        HWidget *base_ = nullptr;
//        SelectArea *selectWidget_ = nullptr;
        SelectWidget *selectWidget_ = nullptr;

    private:
        SelectAttr attr;
        std::vector<SelectActionOption> selectedValues;
        std::vector<SelectActionOption> selectActionOptions;

        // 自定义组件 是否属于focus状态
        bool focus_ = false;

        // select 的children是否响应了click事件
        bool selectChildrenHandleClick = false;
        // select是否处理了mousePress
        bool selectHandleClick = false;
        bool isFirstShow_ = false;
// 属性
    private:
        SelectAttrMode attrMode = SelectAttrMode::none;
        SelectAttrOptions attrOptions;
        uint16_t fixedWidth = 300;
        uint16_t selectHeight = 200;
        GeneralAttrSize attrSize = GeneralAttrSize::middle;
    public:
        void setAttrMode(SelectAttrMode mode);

        void setAttrSize(GeneralAttrSize generalAttrSize);

        void setAttrOptions(const SelectAttrOptions &selectAttrOptions);

        SelectAttrMode getAttrMode() const;
    };


}
