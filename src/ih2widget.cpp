#include <QImage>
#include <QPixmap>
#include <QSpinBox>
#include <QThread>
#include <QWidget>

#include "ihwidget.hpp"
#include "ih2widget.hpp"
#include "tools.hpp"

IH2Widget::IH2Widget(QWidget* parent)
    : IHWidget(parent),
      mKochFractal(Q_NULLPTR),
      mProcessor(Q_NULLPTR),
      mProcessorThread(Q_NULLPTR),
      mIterations(DEFAULT_ITERATIONS)
{
    mTaskDescription.setText("Variant:\t4-4\n"
                             "Fractal:\tKoch snowflake;\n");
    mInfoLayout.addWidget(&mTaskDescription);

    mTaskImage.setPixmap(QPixmap::fromImage(QImage("res/ih2.jpg")));
    mInfoLayout.addWidget(&mTaskImage);

    mIterationsLabel.setText("Iterations:");
    mIterationsSpinBox.setMinimum(MINIMUM_ITERATIONS);
    mIterationsSpinBox.setValue(DEFAULT_ITERATIONS);
    mIterationsSpinBox.setMaximum(MAXIMUM_ITERATIONS);
    connect(&mIterationsSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int value) {
        mIterations = value;
    });
    mParametersLayout.addWidget(&mIterationsLabel, 0, 0);
    mParametersLayout.addWidget(&mIterationsSpinBox, 0, 1);

    mBuildButtonLabel.setText("Click to build:");
    mBuildButton.setText("Build");
    connect(&mBuildButton, &QPushButton::clicked,
            this, [this]() {
        if (mKochFractal != Q_NULLPTR)
        {
            delete mKochFractal;
            mKochFractal = Q_NULLPTR;
        }

        mKochFractal = new KochFractal(IMAGE_WIDTH, IMAGE_HEIGHT);
        mKochFractal->setIterations(mIterations);

        mProcessorThread = new QThread();
        mProcessor = new KochFractalProcessor(mKochFractal);
        mProcessor->moveToThread(mProcessorThread);

        connect(mProcessorThread, &QThread::started,
                this, [this]() { mBuildButton.setEnabled(false); });
        connect(mProcessorThread, &QThread::started,
                mProcessor, &KochFractalProcessor::process);

        connect(mProcessor, &KochFractalProcessor::finished,
                this, [this]() {
            delete mProcessor;
            mProcessor = Q_NULLPTR;

            mProcessorThread->exit();
            mProcessorThread = Q_NULLPTR;

            QImage treeImage = mKochFractal->getTreeImage();
            mTreeImage.setFixedSize(treeImage.width(), treeImage.height());
            mTreeImage.setPixmap(QPixmap::fromImage(treeImage));

            mBuildButton.setEnabled(true);
        });

        mProcessorThread->start();
    });
    mParametersLayout.addWidget(&mBuildButtonLabel, 1, 0);
    mParametersLayout.addWidget(&mBuildButton, 1, 1);

    mInfoLayout.addLayout(&mParametersLayout);

    mTreeImageArea.setMinimumSize(IMAGE_WIDTH * 2, 140 + SCROLL_BAR_MARGIN);
    mTreeImageArea.setMaximumHeight(160);
    mTreeImageArea.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    mTreeImageArea.setWidget(&mTreeImage);

    mImagesLayout.addWidget(&mTreeImageArea);

    mMainLayout.addLayout(&mImagesLayout);
}
