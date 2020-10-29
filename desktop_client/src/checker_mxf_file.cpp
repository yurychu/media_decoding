

#include <desktop_client/checker_mxf_file.hpp>

#include <mxf_specific_parameters_lib/MxfInfo.hpp>

/*
 *
{
    "FormatVersion": {
        "ExpectedValue": "1.1"
    },
    "IndexTableValues": {
        "Slice count": {
            "CompareRules": {
                "ComparatorMain": {
                    "Operator": "=",
                    "Value": 0
                }
            }
        }
    },
    "RIPPresence": {
        "ExpectedValue": true
    },
    "Resolution": {
        "Stored Resolution": {
            "H": {
                "ExpectedValue": 0
            },
            "W": {
                "ExpectedValue": 0
            }
        }
    },
    "VideoLineMap": {
        "Field1": {
            "ExpectedValue": 0
        },
        "Field2": {
            "ExpectedValue": 0
        }
    }
}
 */

#include <string>

// common code
template<typename Enum>
struct EnableBitMaskOperators
{
    static const bool enable = false;
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator |(Enum lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
            static_cast<underlying>(lhs) |
            static_cast<underlying>(rhs)
    );
}


#define ENABLE_BITMASK_OPERATORS(x)  \
template<>                           \
struct EnableBitMaskOperators<x>     \
{                                    \
    static const bool enable = true; \
};


enum class OpsCompare : uint8_t
{
    None =      0x00u,  // 0
    Equal =     0x01u,  // =
    Greater =   0x02u,  // >
    Less =      0x04u,  // <
    Not =       0x08u,  // !
    NotEqual =       Not | Equal,      // !=
    GreaterOrEqual = Greater | Equal,  // >=
    LessOrEqual =    Less | Equal      // <=
};
ENABLE_BITMASK_OPERATORS(OpsCompare)


OpsCompare sym_to_ops_compare(int8_t symbol)
{
    switch (symbol) {
        case ('='):{
            return OpsCompare::Equal;
        } break;
        case ('>'):{
            return OpsCompare::Greater;
        } break;
        case ('<'):{
            return OpsCompare::Less;
        } break;
        case ('!'):{
            return OpsCompare::Not;
        } break;
        default:{
            return OpsCompare::None;
        }
    }
}


class Comparator
{
public:
    Comparator()
            : m_opCompare{OpsCompare::None}
    {}

    explicit Comparator(OpsCompare op)
            : m_opCompare{op}
    {}

    ~Comparator() = default;

    bool empty() const { return m_opCompare == OpsCompare::None; }

    std::string str() const {
        thread_local static std::map<OpsCompare, std::string> dict {
                {OpsCompare::None, "None"},
                {OpsCompare::Equal, "Equal"},
                {OpsCompare::NotEqual, "Not Equal"},
                {OpsCompare::Greater, "Greater"},
                {OpsCompare::Less, "Less"},
                {OpsCompare::GreaterOrEqual, "Greater or equal"},
                {OpsCompare::LessOrEqual, "Less or equal"}
        };
        const auto found = dict.find(m_opCompare);
        if (found != dict.end()){
            return found->second;
        }
        return "";
    }

    static Comparator from_string(const std::string & str){
        OpsCompare op_comp1 = sym_to_ops_compare(str.at(0));
        OpsCompare op_comp2 = OpsCompare::None;
        if (str.size() > 1){
            op_comp2 = sym_to_ops_compare(str.at(1));
        }
        const auto res_op_comp = op_comp1 | op_comp2;
        return Comparator{ res_op_comp };
    }

private:
    OpsCompare m_opCompare;

};


// checker functions

void check_format_version(mxf_info::MxfInfo &mxf_info, std::stringstream &ss, const QJsonObject &obj)
{
    const auto expected_value = obj["ExpectedValue"].toString().toStdString();
    const auto actual_value = mxf_info.getFormatVersion();
    const auto is_equal = (expected_value == actual_value);
    if (is_equal){
        ss << "SUCCESS" << std::endl;
        ss << "Actual: " << actual_value << " equal Expected: " << expected_value << std::endl;
    }
    else {
        ss << "FAILED" << std::endl;
        ss << "Actual: " << actual_value << " not equal Expected: " << expected_value << std::endl;
    }
}


void check_index_table_values(mxf_info::MxfInfo &mxf_info, std::stringstream &ss, const QJsonObject &obj)
{
    const auto actual_big_struct = mxf_info.getIndexTableValues();
    if (obj.contains("Duration")){
        const auto op_comp = obj["Duration"]["CompareRules"]["ComparatorMain"]["Operator"].toString().toStdString();
        const auto comparator = Comparator::from_string(op_comp);
        ss << "Comparator: " << comparator.str() << std::endl;
    }
    if (obj.contains("Edit Unit Byte Count")){

    }
    if (obj.contains("Position Table Count")){

    }
    if (obj.contains("Slice count")){

    }


}


void check_rip_resence(mxf_info::MxfInfo &mxf_info, std::stringstream &ss, const QJsonObject &obj)
{
    const auto expected_value = obj["ExpectedValue"].toBool();
    const auto actual_value = mxf_info.getRIPPresence();
    const auto is_equal = expected_value == actual_value;
    if (is_equal){
        ss << "SUCCESS" << std::endl;
        ss << "Actual: " << std::boolalpha << actual_value
        << " equal Expected: " << std::boolalpha << expected_value << std::endl;
    }
    else {
        ss << "FAILED" << std::endl;
        ss << "Actual: " << std::boolalpha << actual_value
        << " not equal Expected: " << std::boolalpha << expected_value << std::endl;
    }

}


void check_resolution(mxf_info::MxfInfo &mxf_info, std::stringstream &ss, const QJsonObject &obj)
{

}


void check_video_line_map(mxf_info::MxfInfo &mxf_info, std::stringstream &ss, const QJsonObject &obj)
{

}


void check_file_with_out(std::stringstream &ss, const QString &filePath, const QJsonObject &obj)
{
    mxf_info::MxfInfo mxf_info {filePath.toStdString()};

    if (obj.contains("FormatVersion")){
        ss << "-----FormatVersion-----" << std::endl;
        check_format_version(mxf_info, ss, obj["FormatVersion"].toObject());
        ss << "-----------------------" << std::endl;
    }
    if (obj.contains("IndexTableValues")){
        ss << "-----IndexTableValues-----" << std::endl;
        check_index_table_values(mxf_info, ss, obj["IndexTableValues"].toObject());
        ss << "-----------------------" << std::endl;
    }
    if (obj.contains("RIPPresence")){
        ss << "-----RIPPresence-----" << std::endl;
        check_rip_resence(mxf_info, ss, obj["RIPPresence"].toObject());
        ss << "-----------------------" << std::endl;
    }
    if (obj.contains("Resolution")){
        ss << "-----Resolution-----" << std::endl;
        check_resolution(mxf_info, ss, obj["Resolution"].toObject());
        ss << "-----------------------" << std::endl;
    }
    if (obj.contains("VideoLineMap")){
        ss << "-----VideoLineMap-----" << std::endl;
        check_video_line_map(mxf_info, ss, obj["VideoLineMap"].toObject());
        ss << "-----------------------" << std::endl;
    }

}
