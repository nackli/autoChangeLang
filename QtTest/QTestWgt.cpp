#include "QTestWgt.h"
#include <QLabel>
#include <QPushButton>
#include "QChangeTipBtn.h"
#include "QStyleSheetManage.h"

QTestWgt::QTestWgt(QWidget *parent)
	: QWidget(parent)
{
	OnCreateGui();
}

QTestWgt::~QTestWgt()
{
}

void QTestWgt::OnCreateGui()
{
	this->setObjectName("tset");
	m_pMainHLayout = new QHBoxLayout(this);
	QHBoxLayout *pTestLayout = new QHBoxLayout(this);
	m_pMainHLayout->addLayout(pTestLayout);
	
	QWidget* pWgt = new QWidget;
	pWgt->setObjectName("Nack");
	pTestLayout->addWidget(pWgt);

	QLabel* pLabName = new QLabel(this);
	pLabName->setObjectName("labTitle");
	m_pMainHLayout->addWidget(pLabName);
	
	QLabel* pLabName1 = new QLabel(this);
	pLabName1->setObjectName("labTitle1");
	m_pMainHLayout->addWidget(pLabName1);

	QLabel* pLabName2 = new QLabel(this);
	pLabName2->setObjectName("labTitle2");
	m_pMainHLayout->addWidget(pLabName2);

	QLabel* pLabName3 = new QLabel(this);
	pLabName3->setObjectName("labTitle3");
	m_pMainHLayout->addWidget(pLabName3);

	QChangeTipBtn* pBtnChange = new QChangeTipBtn(this);
	pBtnChange->setObjectName("btnChange");
	//pBtnChange->setCheckable(true);
	m_pMainHLayout->addWidget(pBtnChange);
	//QObject::connect(pBtnChange, &QPushButton::clicked, pBtnChange, &QPushButton::hide);
	connect(pBtnChange, SIGNAL(pressed()), this, SLOT(OnSlotChangeStyleBtn()));
	this->setLayout(m_pMainHLayout);
}

void QTestWgt::OnSlotChangeStyleBtn()
{
	static int iIndex = 0;
	switch (iIndex % 5)
	{
	case 0:
		QStyleSheetManage::OnLoadStyleSheet("test.qss", "./Language/Lang_en.txt");
		break;
	case 1:
		QStyleSheetManage::OnLoadStyleSheet("test.qss", "./Language/Lang_de.txt");
		break;
	case 2:
		QStyleSheetManage::OnLoadStyleSheet("test.qss", "./Language/Lang_fr.txt");
		break;
	case 3:
		QStyleSheetManage::OnLoadStyleSheet("test.qss", "./Language/Lang_ar-dz.txt");
		break;
	case 4:
		QStyleSheetManage::OnLoadStyleSheet("test.qss", "./Language/Lang_zh.txt");
		break;
	}
	QChangeTipBtn* pBtnChange = (QChangeTipBtn*)this->sender();
	pBtnChange->OnSetChangeStatus(iIndex % 2);
	iIndex++;
	//pBtnChange->setChecked(!pBtnChange->isChecked());	
}